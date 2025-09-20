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

#include <common/log/log.h>
#include <storage/db/db.h>

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/table/view.h"

UpdateStmt::UpdateStmt(BaseTable *table, std::vector<FieldMeta> field_metas,
    std::vector<std::unique_ptr<Expression>> values, FilterStmt *filter_stmt)
    : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values)), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, UpdateSqlNode &update_sql, Stmt *&stmt)
{
  // TODO
  const char *table_name = update_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update_sql.set_clauses.empty()) {
    std::ostringstream set_clauses_logger;
    set_clauses_logger << "invalid argument. db=" << db << ", table_name=" << table_name;
    set_clauses_logger << ", set_clauses=[";
    for (const auto &clause : update_sql.set_clauses) {
      // 实现表达式打印
      // set_clauses_logger << "{" << clause.field_name << ": " << clause.value.to_string() << "}, ";
      set_clauses_logger << "{" << clause.field_name << ": "
                         << "}, ";
    }
    set_clauses_logger << "]";
    LOG_WARN("%s", set_clauses_logger.str().c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  auto table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (table->type() == TableType::View && !table->is_mutable()) {
    LOG_ERROR("The target table %s of the UPDATE is not updatable", table->name());
    return RC::READ_ONLY_VIEW_UPDATE_ERROR;
  }

  auto                                     table_meta = table->table_meta();
  std::vector<FieldMeta>                   field_metas;
  std::vector<std::unique_ptr<Expression>> values;

  RC rc = RC::SUCCESS;
  for (auto &clause : update_sql.set_clauses) {
    // check whether the field exists
    auto field_meta = table_meta.field(clause.field_name.c_str());
    if (field_meta == nullptr) {
      LOG_WARN("Field does not exist. db=%s, table_name=%s, field_name=%s",
                db->name(), table_name, clause.field_name.c_str());
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    if (!field_meta->is_mutable()) {
      LOG_ERROR("Column '%s' is not updateable", field_meta->name());
      return RC::EXPRESSION_FIELD_NOT_UPDATEABLE;
    }

    // check whether the value is valid
    std::unordered_map<std::string, BaseTable *> table_map;
    table_map.insert(std::pair(std::string(table_name), table));

    vector<unique_ptr<Expression>> expressions;
    BinderContext                  binder_context;

    binder_context.add_table(table);
    binder_context.add_db(db);
    binder_context.set_tables(&table_map);
    binder_context.set_default_table(table);

    ExpressionBinder expression_binder(binder_context);
    rc = expression_binder.bind_expression(clause.value, expressions);

    if (OB_FAIL(rc)) {
      LOG_WARN("Failed to bind expression for field: %s",
                clause.field_name.c_str());
      return rc;
    }

    // 表达式值类型检查延迟到 UpdatePhysicalOperator 阶段

    field_metas.emplace_back(*field_meta);
    values.emplace_back(std::move(expressions[0]));
  }

  std::unordered_map<std::string, BaseTable *> table_map;
  table_map.insert(std::pair(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(db, table, {}, &table_map, update_sql.conditions, filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, std::move(field_metas), std::move(values), filter_stmt);
  return RC::SUCCESS;
}
