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
#include "sql/parser/value.h"
#include "sql/stmt/stmt.h"

class Table;
class Db;

/**
 * @brief 插入语句
 * @ingroup Statement
 */
class InsertStmt : public Stmt
{
public:
  InsertStmt() = default;
  InsertStmt(Table *table, const std::vector<std::vector<Value>> values, int value_amount, int num);

  StmtType type() const override { return StmtType::INSERT; }

public:
  static RC create(Db *db, const InsertSqlNode &insert_sql, Stmt *&stmt);

public:
  Table                                 *table() const { return table_; }
  const std::vector<std::vector<Value>> &values() const { return values_; }
  int                                    value_amount() const { return value_amount_; }

  static RC          type_convert(AttrType value_type, AttrType file_type, const Value &value,bool nullable);
  static std::string extractDigits_int(const std::string &str);
  static std::string extractDigits_float(const std::string &str);

private:
  Table                                *table_ = nullptr;
  const std::vector<std::vector<Value>> values_;
  int                                   value_amount_ = 0;
  int                                   values_num_   = 0;
};
