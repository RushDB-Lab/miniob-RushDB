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

UpdateStmt::UpdateStmt(Table *table, const char *attribute_name, const Value *values, FilterStmt *filter_stmt)
    : table_(table), attribute_name_(attribute_name), values_(values), filter_stmt_(filter_stmt)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update_sql, Stmt *&stmt)
{
  // TODO
  const char *table_name = update_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || update_sql.attribute_name.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, attribute_name=%s",
        db, table_name, update_sql.attribute_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  // check whether the field exists
  auto field_meta = table->table_meta().field(update_sql.attribute_name.c_str());
  if (field_meta == nullptr) {
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  // check whether the value valid
  const Value *value = &update_sql.value;
  if (value->attr_type() == AttrType::INTS && field_meta->type() == AttrType::FLOATS) {
    // do nothing，但是好像不用考虑类型转换
  } else if (value->attr_type() != field_meta->type()) {
    LOG_ERROR("Schema field type mismatch. Field: %s, Expected Type: %s, Provided Type: %s",
              field_meta->name(),
              attr_type_to_string(field_meta->type()),
              attr_type_to_string(value->attr_type()));
    return RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else if (value->length() > field_meta->len()) {
    LOG_ERROR("Value length exceeds maximum allowed length for field. Field: %s, Type: %s, Offset: %d, Length: %d, Max Length: %d",
              field_meta->name(),
              attr_type_to_string(field_meta->type()),
              field_meta->offset(),
              value->length(),
              field_meta->len());
    return RC::VALUE_TOO_LONG;
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
  stmt = new UpdateStmt(table, update_sql.attribute_name.c_str(), value, filter_stmt);
  return RC::SUCCESS;
}
