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
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include <vector>

#include "sql/expr/expression.h"

class BinderContext
{
public:
  BinderContext()          = default;
  virtual ~BinderContext() = default;

  void add_table(BaseTable *table) { query_tables_.emplace_back(table); }
  void add_db(Db *db) { db_ = db; }

  void set_tables(std::unordered_map<std::string, BaseTable *> *tables) { tables_ = tables; }

  Db *get_db() const { return db_; }

  BaseTable *find_table(const char *table_name) const;

  const std::vector<BaseTable *>               &query_tables() const { return query_tables_; }
  std::unordered_map<std::string, BaseTable *> &table_map() { return *tables_; }

  // 对于 update delete 目前还不支持给表取别名，所以是空的
  bool has_tables_alias() { return !tables_alias_.empty(); }

  const std::vector<std::string> &alias() { return tables_alias_; }

  void set_alias(std::vector<std::string> alias) { tables_alias_ = std::move(alias); }

private:
  Db *db_;

public:
  [[nodiscard]] BaseTable *default_table() const { return default_table_; }
  void                     set_default_table(BaseTable *default_table) { default_table_ = default_table; }

private:
  BaseTable                                    *default_table_;
  std::vector<BaseTable *>                      query_tables_;
  std::vector<std::string>                      tables_alias_;
  std::unordered_map<std::string, BaseTable *> *tables_;
};

/**
 * @brief 绑定表达式
 * @details 绑定表达式，就是在SQL解析后，得到文本描述的表达式，将表达式解析为具体的数据库对象
 */
class ExpressionBinder
{
public:
  ExpressionBinder(BinderContext &context) : context_(context) { multi_tables_ = context_.query_tables().size() > 1; }

  virtual ~ExpressionBinder() = default;

  RC bind_expression(std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

private:
  RC bind_star_expression(
      std::unique_ptr<Expression> &star_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_unbound_field_expression(
      std::unique_ptr<Expression> &unbound_field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_field_expression(
      std::unique_ptr<Expression> &field_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_value_expression(
      std::unique_ptr<Expression> &value_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_cast_expression(
      std::unique_ptr<Expression> &cast_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_comparison_expression(
      std::unique_ptr<Expression> &comparison_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_conjunction_expression(
      std::unique_ptr<Expression> &conjunction_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_arithmetic_expression(
      std::unique_ptr<Expression> &arithmetic_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_function_expression(
      std::unique_ptr<Expression> &aggregate_expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_subquery_expression(
      std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);
  RC bind_exprlist_expression(
      std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions);

  void wildcard_fields(BaseTable *table, std::string table_alias, vector<unique_ptr<Expression>> &expressions,
      bool multi_tables = false);

private:
  bool           multi_tables_;
  BinderContext &context_;
};
