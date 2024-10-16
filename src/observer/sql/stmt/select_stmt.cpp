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
// Created by Wangyunlai on 2022/6/6.
//

#include "sql/stmt/select_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/parser/expression_binder.h"

using namespace std;
using namespace common;

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}

RC SelectStmt::create(Db *db, SelectSqlNode &select_sql, Stmt *&stmt,
    const std::unordered_map<std::string, BaseTable *> &parent_table_map)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }

  BinderContext binder_context;

  // collect tables in `from` statement
  vector<BaseTable *>                tables;
  unordered_map<string, BaseTable *> table_map = parent_table_map;
  unordered_map<string, BaseTable *> temp_map;
  std::vector<std::string>           tables_alias(select_sql.relations.size());

  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].relation.c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    BaseTable *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
    // 建立别名
    auto &table_alias = select_sql.relations[i].alias;
    if (!table_alias.empty()) {
      const auto &success = temp_map.emplace(table_alias, table);
      if (!success.second)
        return RC::INVALID_ALIAS;
    } else {
      temp_map.emplace(table_name, table);
    }

    tables_alias[i] = table_alias;
    tables.emplace_back(table);
    binder_context.add_table(table);
  }

  // alias is all avaliable
  table_map.insert(temp_map.begin(), temp_map.end());

  BaseTable *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  binder_context.set_alias(tables_alias);
  binder_context.set_tables(&table_map);
  binder_context.set_default_table(default_table);
  // collect query fields in `select` statement
  vector<unique_ptr<Expression>> bound_expressions;
  ExpressionBinder               expression_binder(binder_context);

  for (unique_ptr<Expression> &expression : select_sql.expressions) {
    RC rc = expression_binder.bind_expression(expression, bound_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> group_by_expressions;
  for (unique_ptr<Expression> &expression : select_sql.group_by) {
    RC rc = expression_binder.bind_expression(expression, group_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  vector<unique_ptr<Expression>> order_by_expressions;
  for (OrderBySqlNode &unit : select_sql.order_by) {
    RC rc = expression_binder.bind_expression(unit.expr, order_by_expressions);
    if (OB_FAIL(rc)) {
      LOG_INFO("bind expression failed. rc=%s", strrc(rc));
      return rc;
    }
  }

  std::vector<OrderBySqlNode> order_by_;
  order_by_.reserve(order_by_expressions.size());
  for (size_t i = 0; i < order_by_expressions.size(); i++) {
    order_by_.push_back({std::move(order_by_expressions[i]), select_sql.order_by[i].is_asc});
  }

  int limit = -1;
  if (select_sql.limit) {
    limit = select_sql.limit->number;
  }

  // create filter statement in `where` statement
  FilterStmt *filter_stmt = nullptr;
  RC rc = FilterStmt::create(db, default_table, binder_context.alias(), &table_map, select_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // create filter statement in `having` statement
  FilterStmt *having_filter_stmt = nullptr;
  rc                             = FilterStmt::create(
      db, default_table, binder_context.alias(), &table_map, select_sql.having_conditions, having_filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct having filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();

  select_stmt->tables_.swap(tables);
  select_stmt->tables_alias_ = std::move(tables_alias);
  select_stmt->query_expressions_.swap(bound_expressions);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->group_by_.swap(group_by_expressions);
  select_stmt->order_by_.swap(order_by_);
  select_stmt->limit_              = limit;
  select_stmt->having_filter_stmt_ = having_filter_stmt;
  stmt                             = select_stmt;
  return RC::SUCCESS;
}
