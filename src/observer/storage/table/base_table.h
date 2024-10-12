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
  virtual RC make_record(int value_num, const Value *values, Record &record) = 0;

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

protected:
  TableType       type_             = TableType::Unknown;
  TableMeta       table_meta_       = TableMeta();
  DiskBufferPool *data_buffer_pool_ = nullptr;  /// 数据文件关联的buffer pool
};
