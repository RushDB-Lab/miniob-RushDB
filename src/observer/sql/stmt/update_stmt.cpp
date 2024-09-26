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

#include "sql/stmt/update_stmt.h"
#include "sql/stmt/filter_stmt.h"

#include <common/log/log.h>
#include <storage/db/db.h>

#include <utility>

UpdateStmt::UpdateStmt(
    Table *table, std::vector<FieldMeta> field_metas, std::vector<Value> values, FilterStmt *filter_stmt)
    : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values)), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt)
{
  // TODO
  const char *table_name = update_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update_sql.set_clauses.empty()) {
    std::ostringstream set_clauses_logger;
    set_clauses_logger << "invalid argument. db=" << db << ", table_name=" << table_name;
    set_clauses_logger << ", set_clauses=[";
    for (const auto &clause : update_sql.set_clauses) {
      set_clauses_logger << "{" << clause.field_name << ": " << clause.value.to_string() << "}, ";
    }
    set_clauses_logger << "]";
    LOG_WARN("%s", set_clauses_logger.str().c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  auto                   table_meta = table->table_meta();
  std::vector<FieldMeta> field_metas;
  std::vector<Value>     values;

  for (auto &clause : update_sql.set_clauses) {
    // check whether the field exists
    auto field_meta = table_meta.field(clause.field_name.c_str());
    if (field_meta == nullptr) {
      LOG_WARN("no such field. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_FIELD_NOT_EXIST;
    }

    // check whether the value valid
    auto value = clause.value;
    if (value.attr_type() != field_meta->type()) {
      // 尝试转换，发生转换时不考虑数值溢出
      Value to_value;
      RC    rc = Value::cast_to(value, field_meta->type(), to_value);
      if (rc != RC::SUCCESS) {
        LOG_ERROR("Schema field type mismatch and cast to failed. Field: %s, Expected Type: %s, Provided Type: %s",
                  field_meta->name(),
                  attr_type_to_string(field_meta->type()),
                  attr_type_to_string(value.attr_type()));
        return RC::SCHEMA_FIELD_TYPE_MISMATCH;
      }
      // 转换成功
      value = std::move(to_value);
    } else if (value.length() > field_meta->len()) {
      LOG_ERROR("Value length exceeds maximum allowed length for field. Field: %s, Type: %s, Offset: %d, Length: %d, Max Length: %d",
                field_meta->name(),
                attr_type_to_string(field_meta->type()),
                field_meta->offset(),
                value.length(),
                field_meta->len());
      return RC::VALUE_TOO_LONG;
    }

    field_metas.emplace_back(*field_meta);
    values.emplace_back(value);
  }

  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(std::string(table_name), table));

  FilterStmt *filter_stmt = nullptr;
  RC          rc          = FilterStmt::create(
      db, table, &table_map, update_sql.conditions.data(), static_cast<int>(update_sql.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create filter statement. rc=%d:%s", rc, strrc(rc));
    return rc;
  }

  // everything alright
  stmt = new UpdateStmt(table, field_metas, values, filter_stmt);
  return RC::SUCCESS;
}
