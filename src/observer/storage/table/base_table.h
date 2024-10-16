/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                   *
 * @Description : table base class                             *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include <span>

#include "storage/record/record.h"
#include "storage/table/table_meta.h"
#include "storage/buffer/disk_buffer_pool.h"

class Db;

enum class TableType
{
  Unknown,
  Table,
  View
};

class BaseTable
{
public:
  virtual ~BaseTable() = default;

  TableType        type() const { return type_; }
  int32_t          table_id() const { return table_meta_.table_id(); }
  const TableMeta &table_meta() const { return table_meta_; }
  const char      *name() const { return table_meta_.name(); }

  /**
   * @brief 根据给定的字段生成一个记录/行
   * @details 通常是由用户传过来的字段，按照schema信息组装成一个record。
   * @param value_num 字段的个数
   * @param values    每个字段的值
   * @param record    生成的记录数据
   */
  RC make_record(int value_num, const Value *values, Record &record)
  {
    RC rc = RC::SUCCESS;
    // 检查字段类型是否一致
    if (value_num + table_meta_.sys_field_num() != table_meta_.field_num()) {
      LOG_WARN("Input values don't match the table's schema, table name:%s", table_meta_.name());
      return RC::SCHEMA_FIELD_MISSING;
    }

    const int normal_field_start_index = table_meta_.sys_field_num();
    // 复制所有字段的值
    int   record_size = table_meta_.record_size();
    char *record_data = (char *)malloc(record_size);
    memset(record_data, 0, record_size);

    for (int i = 0; i < value_num && OB_SUCC(rc); i++) {
      const FieldMeta *field = table_meta_.field(i + normal_field_start_index);
      const Value     &value = values[i];
      // 判断是否在 NOT NULL 字段设置 NULL 值
      if (value.is_null()) {
        if (!field->nullable()) {
          return RC::NOT_NULLABLE_VALUE;
        }
        record_data[field->offset() + field->len() - 1] = '1';
      } else {
        Value real_value = value;
        if (field->type() != value.attr_type()) {
          if (field->type() == AttrType::TEXTS && value.attr_type() == AttrType::CHARS) {
            // 对于超长文本通过借用的方法减少拷贝
            rc = real_value.borrow_text(value);
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to borrow text value. table name:%s, field name:%s, value length:%d",
                table_meta_.name(), field->name(), value.length());
              break;
            }
          } else {
            // 插入不允许非目标类型的类型提升
            rc = Value::cast_to(value, field->type(), real_value, false);
            if (OB_FAIL(rc)) {
              LOG_WARN("failed to cast value. table name:%s, field name:%s, value:%s",
                table_meta_.name(), field->name(), value.to_string().c_str());
              break;
            }
          }
        }
        // 进行长度校验
        if (real_value.length() > field->len() - field->nullable()) {
          LOG_ERROR("Value length exceeds maximum allowed length for field. Field: %s, Type: %s, Offset: %d, Length: %d, Max Length: %d",
                  field->name(),
                  attr_type_to_string(field->type()),
                  field->offset(),
                  value.length(),
                  field->len());
          return RC::VALUE_TOO_LONG;
        }
        rc = set_value_to_record(record_data, real_value, field);
      }
    }

    if (OB_FAIL(rc)) {
      LOG_WARN("failed to make record. table name:%s", table_meta_.name());
      free(record_data);
      return rc;
    }

    record.set_data_owner(record_data, record_size);
    return RC::SUCCESS;
  }

  RC set_value_to_record(char *record_data, const Value &value, const FieldMeta *field)
  {
    size_t       copy_len = field->len();
    const size_t data_len = value.length();
    if (field->type() == AttrType::CHARS || field->type() == AttrType::TEXTS) {
      if (copy_len > data_len) {
        copy_len = data_len + 1;
      }
    }
    if (field->type() == AttrType::VECTORS) {
      if (copy_len > data_len) {
        copy_len = data_len;
      }
    }
    // text 类型的话最多存 65535 字节，超出则报错
    memcpy(record_data + field->offset(), value.data(), copy_len);
    return RC::SUCCESS;
  }

  /**
   * @brief 可以在页面锁保护的情况下访问记录
   * @details 当前是在事务中访问记录，为了提供一个“原子性”的访问模式
   * @param rid
   * @param visitor
   * @return RC
   */
  virtual RC visit_record(const RID &rid, const function<bool(Record &)> &visitor) = 0;

  virtual RC insert_record(Record &record)                                     = 0;
  virtual RC delete_record(const Record &record)                               = 0;
  virtual RC delete_record(const RID &rid)                                     = 0;
  virtual RC update_record(const Record &old_record, const Record &new_record) = 0;
  virtual RC get_record(const RID &rid, Record &record)                        = 0;

  virtual RC drop() = 0;

  virtual RC sync() = 0;

  bool is_mutable() const { return mutable_; }

protected:
  Db    *db_ = nullptr;
  string base_dir_;
  bool mutable_ = true;  // 当前仅对视图可用，是否是只读视图，即包括聚合函数或 groupby having 语句
  TableType       type_             = TableType::Unknown;
  TableMeta       table_meta_       = TableMeta();
  DiskBufferPool *data_buffer_pool_ = nullptr;  /// 数据文件关联的buffer pool
};
