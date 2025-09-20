/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#pragma once

#include "common/rc.h"
#include "sql/stmt/stmt.h"

class BaseTable;
class Db;

/**
 * @brief 插入语句
 * @ingroup Statement
 */
class InsertStmt : public Stmt
{
public:
  InsertStmt() = delete;
  InsertStmt(BaseTable *table, std::vector<std::vector<Value>> values_list);

  StmtType type() const override { return StmtType::INSERT; }

  static RC create(Db *db, const InsertSqlNode &insert_sql, Stmt *&stmt);

  BaseTable                             *table() const { return table_; }
  const std::vector<std::vector<Value>> &values_list() const { return values_list_; };

private:
  BaseTable                      *table_ = nullptr;
  std::vector<std::vector<Value>> values_list_;
};
