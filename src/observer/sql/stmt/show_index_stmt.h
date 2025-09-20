/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/29                                    *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "sql/stmt/stmt.h"

/**
 * @brief 描述表的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class ShowIndexStmt : public Stmt
{
public:
  ShowIndexStmt(const std::string &table_name);
  ~ShowIndexStmt() override = default;

  StmtType type() const override { return StmtType::SHOW_INDEX; }

  const std::string &table_name() const { return table_name_; }

  static RC create(Db *db, const ShowIndexSqlNode &show_index, Stmt *&stmt);

private:
  const std::string &table_name_;
};
