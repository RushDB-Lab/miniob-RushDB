/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "storage/db/db.h"
#include "storage/table/base_table.h"
#include "sql/operator/physical_operator.h"

class View : public BaseTable
{
public:
  View()           = default;
  ~View() override = default;

  /**
   * 创建一个表
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attributes 字段
   */
  RC create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
      span<const AttrInfoSqlNode> attributes, std::unique_ptr<PhysicalOperator> select_oper,
      StorageFormat storage_format);

  RC drop() override;

  /**
   * @brief 根据给定的字段生成一个记录/行
   * @details 通常是由用户传过来的字段，按照schema信息组装成一个record。
   * @param value_num 字段的个数
   * @param values    每个字段的值
   * @param record    生成的记录数据
   */
  RC make_record(int value_num, const Value *values, Record &record) override;

  RC insert_record(Record &record) override;
  RC delete_record(const Record &record) override;
  RC delete_record(const RID &rid) override;
  RC update_record(const Record &old_record, const Record &new_record) override;
  RC get_record(const RID &rid, Record &record) override;
  RC visit_record(const RID &rid, const function<bool(Record &)> &visitor) override;

  RC sync() override;

  bool is_mutable() const { return mutable_; }

private:
  Db    *db_ = nullptr;
  string base_dir_;
  // std::unordered_map<Field>
  std::unique_ptr<PhysicalOperator> select_oper_;  // 存储了 select 的物理算子
  bool                              mutable_;      // 是否是只读视图
};
