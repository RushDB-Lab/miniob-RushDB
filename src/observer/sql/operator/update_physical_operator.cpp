/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/17                                    *
 * @Description : UpdatePhysicalOperator source file           *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "update_physical_operator.h"
#include "storage/trx/trx.h"

RC UpdatePhysicalOperator::open(Trx *trx)
{
  if (children_.empty()) {
    return RC::SUCCESS;
  }

  std::unique_ptr<PhysicalOperator> &child = children_[0];

  RC rc = child->open(trx);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to open child operator: %s", strrc(rc));
    return rc;
  }

  trx_ = trx;

  while (OB_SUCC(rc = child->next())) {
    Tuple *tuple = child->current_tuple();
    if (nullptr == tuple) {
      LOG_WARN("failed to get current record: %s", strrc(rc));
      return rc;
    }

    RowTuple *row_tuple = static_cast<RowTuple *>(tuple);
    Record   &record    = row_tuple->record();
    record.set_base_rids(tuple->base_rids());
    records_.emplace_back(std::move(record));
  }

  child->close();

  // 如果需要更新的记录为空，直接返回成功，即使 value 校验异常也应该返回成功
  if (records_.empty()) {
    return RC::SUCCESS;
  }

  // 得到真正的 value，并做校验
  RowTuple           tuple;
  Value              value;
  std::vector<Value> real_values(values_.size());
  SubQueryExpr      *sub_query_expr = nullptr;
  int                size           = static_cast<int>(values_.size());
  for (int i = 0; i < size; ++i) {
    auto &value_expr = values_[i];
    auto &field_meta = field_metas_[i];

    if (value_expr->type() == ExprType::SUBQUERY) {
      sub_query_expr = dynamic_cast<SubQueryExpr *>(value_expr.get());
      rc             = sub_query_expr->open(trx_, tuple);
      if (OB_FAIL(rc)) {
        LOG_ERROR("Failed to open subquery for field: %s",
                  field_meta.name());
        return rc;
      }
    }

    // 得到表达式的值
    rc = value_expr->get_value(tuple, value);
    if (OB_FAIL(rc) && rc != RC::RECORD_EOF) {
      LOG_ERROR("Failed to get value for field: %s",
                  field_meta.name());
      return rc;
    }

    // 如果是子查询只能有一行一列
    if (sub_query_expr && sub_query_expr->has_more_row(tuple)) {
      LOG_ERROR("Subquery returned more than one row for field: %s",
                 field_meta.name());
      return RC::SUBQUERY_RETURNED_MULTIPLE_ROWS;
    }

    // 进行类型校验
    if (value.attr_type() != field_meta.type()) {
      // 尝试转换，发生转换时不考虑数值溢出
      Value to_value;
      // 更新不允许非目标类型的类型提升
      rc = Value::cast_to(value, field_meta.type(), to_value, false);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Schema field type mismatch and cast to failed. Field: %s, Expected Type: %s, Provided Type: %s, Length: %d",
        field_meta.name(),
                  attr_type_to_string(field_meta.type()),
                  attr_type_to_string(value.attr_type()), value.length());
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // 转换成功
      value = std::move(to_value);
    }

    // 进行长度校验
    if (value.length() > field_meta.len() - field_meta.nullable()) {
      LOG_ERROR("Value length exceeds maximum allowed length for field. Field: %s, Type: %s, Offset: %d, Length: %d, Max Length: %d",
                field_meta.name(),
                attr_type_to_string(field_meta.type()),
                field_meta.offset(),
                value.length(),
                field_meta.len());
      return RC::VALUE_TOO_LONG;
    }

    if (sub_query_expr) {
      sub_query_expr->close();
      sub_query_expr = nullptr;
    }

    real_values[i] = std::move(value);
  }

  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证删除的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  Record new_record;
  for (Record &old_record : records_) {
    // rid 得手动拷贝
    new_record.set_rid(old_record.rid());
    new_record.copy_data(old_record.data(), old_record.len());
    for (size_t i = 0; i < field_metas_.size(); ++i) {
      if (field_metas_[i].nullable()) {
        auto null_offset = field_metas_[i].offset() + field_metas_[i].len() - 1;
        if (real_values[i].is_null()) {
          new_record.data()[null_offset] = '1';
        } else {
          new_record.data()[null_offset] = 0;
        }
      } else if (real_values[i].is_null()) {
        rollback();
        return RC::NOT_NULLABLE_VALUE;
      }
      // 只有非 null 值才需要拷贝数据，防止读到垃圾数据
      if (!real_values[i].is_null()) {
        rc = new_record.set_field(field_metas_[i].offset(), field_metas_[i].len(), real_values[i]);
        if (OB_FAIL(rc)) {
          LOG_ERROR("failed to set field: %s", strrc(rc));
          return rc;
        }
      }
    }
    auto rollback_old_record = old_record.clone();
    auto rollback_new_record = new_record.clone();
    rc                       = trx_->update_record(table_, old_record, new_record);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to update record: %s", strrc(rc));
      rollback();
      return rc;
    } else {
      log_records.emplace_back(rollback_old_record, rollback_new_record);
    }
  }

  return RC::SUCCESS;
}

void UpdatePhysicalOperator::rollback()
{
  RC rc;
  for (auto &[rollback_old_record, rollback_new_record] : log_records) {
    rc = trx_->update_record(table_, rollback_new_record, rollback_old_record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to update record: %s", strrc(rc));
    }
  }
}

RC UpdatePhysicalOperator::next() { return RC::RECORD_EOF; }

RC UpdatePhysicalOperator::close() { return RC::SUCCESS; }
