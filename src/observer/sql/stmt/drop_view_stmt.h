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
#include <vector>

#include "sql/stmt/stmt.h"

class Db;

/**
 * @brief 表示删除视图的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class DropViewStmt : public Stmt
{
public:
  explicit DropViewStmt(std::string table_name) : table_name_(std::move(table_name)) {}
  ~DropViewStmt() override = default;

  StmtType type() const override { return StmtType::DROP_VIEW; }

  const std::string &table_name() const { return table_name_; }

  static RC create(Db *db, const DropViewSqlNode &drop_view, Stmt *&stmt);

private:
  std::string table_name_;
};
