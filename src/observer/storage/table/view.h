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
  RC create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir, SelectStmt *select_stmt,
      StorageFormat storage_format);

  RC drop() override;

  RC insert_record(Record &record) override;
  RC delete_record(const Record &record) override;
  RC delete_record(const RID &rid) override;
  RC update_record(const Record &old_record, const Record &new_record) override;
  RC get_record(const RID &rid, Record &record) override;
  RC visit_record(const RID &rid, const function<bool(Record &)> &visitor) override;

  RC sync() override;

  std::unique_ptr<PhysicalOperator> &select_oper() { return select_oper_; }

  bool has_join() { return tables_.size() > 1; }

private:
  // 视图的 field 对应 哪个物理表和对应的 field idx
  std::vector<std::pair<BaseTable *, int>> field_index_;
  std::vector<BaseTable *>                 tables_;
  std::unique_ptr<PhysicalOperator>        select_oper_;  // 存储了 select 的物理算子
};
