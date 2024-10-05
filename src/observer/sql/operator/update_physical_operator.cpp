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

#include <storage/trx/trx.h>

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
    records_.emplace_back(std::move(record));
  }

  child->close();

  // 先收集记录再更新
  // 记录的有效性由事务来保证，如果事务不保证删除的有效性，那说明此事务类型不支持并发控制，比如VacuousTrx
  Record new_record;
  for (Record &old_record : records_) {
    // rid 得手动拷贝
    new_record.set_rid(old_record.rid());
    new_record.copy_data(old_record.data(), old_record.len());
    for (size_t i = 0; i < field_metas_.size(); ++i) {
      new_record.set_field(field_metas_[i].offset(), field_metas_[i].len(), values_[i]);
      if (field_metas_[i].nullable()) {
        auto null_offset = field_metas_[i].offset() + field_metas_[i].len() - 1;
        if (values_[i].is_null()) {
          new_record.data()[null_offset] = '1';
        } else {
          new_record.data()[null_offset] = 0;
        }
      } else {
        if (values_[i].is_null()) {
          rollback();
          return RC::NOT_NULLABLE_VALUE;
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
