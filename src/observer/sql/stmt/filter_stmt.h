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

#include "sql/expr/expression.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/parser/expression_binder.h"
#include <unordered_map>
#include <vector>

class Db;
class Table;
class FieldMeta;

/**
 * @brief Filter/谓词/过滤语句
 * @ingroup Statement
 */
class FilterStmt
{
public:
  FilterStmt() = default;
  virtual ~FilterStmt();

public:
  static RC create(Db *db, BaseTable *default_table, std::vector<std::string> tables_alias,
      std::unordered_map<std::string, BaseTable *> *tables, std::unique_ptr<Expression> &condition, FilterStmt *&stmt);

  bool                         condition_empty() const { return nullptr == condition_; }
  std::unique_ptr<Expression> &condition() { return condition_; }

private:
  RC bind_expressions_recursively(ExpressionBinder &expression_binder, unique_ptr<Expression> &condition,
      vector<unique_ptr<Expression>> &cond_expressions);

private:
  std::unique_ptr<Expression> condition_;
};
