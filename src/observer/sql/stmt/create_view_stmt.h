/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                   *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include <string>
#include <utility>
#include <vector>

#include "sql/stmt/stmt.h"
#include "select_stmt.h"

class Db;

/**
 * @brief 表示创建表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class CreateViewStmt : public Stmt
{
public:
  CreateViewStmt(std::string &table_name, std::vector<std::string> &attr_names, SelectStmt *select_stmt)
      : table_name_(std::move(table_name)), attr_names_(std::move(attr_names)), select_stmt_(select_stmt)
  {}
  ~CreateViewStmt() override = default;

  StmtType type() const override { return StmtType::CREATE_VIEW; }

  std::string              &table_name() { return table_name_; }
  std::vector<std::string> &attr_names() { return attr_names_; }
  SelectStmt               *select_stmt() { return select_stmt_; }

  static RC create(Db *db, CreateViewSqlNode &create_view, Stmt *&stmt);

private:
  std::string              table_name_;
  std::vector<std::string> attr_names_;  // 是否指定了属性名
  SelectStmt              *select_stmt_;
};
