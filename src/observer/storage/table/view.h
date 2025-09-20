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
   * @param attr_names 字段
   * @param select_sql 查询 sql
   * @param select_stmt 查询 stmt
   * @param storage_format 存储格式，与基表一致
   */
  RC create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
      std::vector<std::string> attr_names, std::string select_sql, SelectStmt *select_stmt,
      StorageFormat storage_format);

  RC drop() override;

  /**
   * 打开一个视图
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   */
  RC open(Db *db, const char *meta_file, const char *base_dir) override;

  RC init_data();

  RC init_member();

  RC insert_record(Record &record) override;
  RC delete_record(const Record &record) override;
  RC delete_record(const RID &rid) override;
  RC update_record(const Record &old_record, const Record &new_record) override;
  RC get_record(const RID &rid, Record &record) override;
  RC visit_record(const RID &rid, const function<bool(Record &)> &visitor) override;

  RC sync() override;

  const std::string &select_sql() { return select_sql_; }

  bool has_join() { return tables_.size() > 1; }

private:
  std::string select_sql_;  // 持久化，运行时也只能存解析后的 sql，因为涉及独占资源的移动
  std::vector<BaseTable *> tables_;  // 可能含视图和基表，所以要在所有表都加载好再处理
  std::vector<std::pair<BaseTable *, int>> field_index_;  // 视图的 field 对应 哪个物理表和对应的 field idx
};
