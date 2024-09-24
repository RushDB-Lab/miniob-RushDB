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
#include "common/log/log.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"

UpdateStmt::UpdateStmt(Table *table, std::vector<updateNode> updatenodes_, int value_amount)
    : table_(table), updatenodes(updatenodes_), value_amount_(value_amount)
{}

RC UpdateStmt::create(Db *db, const UpdateSqlNode &update, Stmt *&stmt)
{
  RC rc = RC::SUCCESS;

  // check whether the table exists
  const char *table_name = update.relation_name.c_str();
  Table      *table      = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  for (auto node : update.update_nodes) {
    const char      *att_name = node.attribute_name.c_str();
    const FieldMeta *filed    = table->find_fieldmate_by_name(att_name);
    if (nullptr == db || nullptr == table_name || nullptr == att_name || 0 == filed ||
        !filed->nullable() && node.value.attr_type() == null) {
      return RC::INVALID_ARGUMENT;
    }
  }

  // create filter statement in `where` statement
  std::unordered_map<std::string, Table *> table_map;
  table_map.insert(std::pair<std::string, Table *>(table_name, table));

  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(
      db, table, &table_map, update.conditions.data(), static_cast<int>(update.conditions.size()), filter_stmt);
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // ALL RIGHT
  UpdateStmt *Update_stmt   = new UpdateStmt(table, update.update_nodes, update.update_nodes.size());
  Update_stmt->filter_stmt_ = filter_stmt;
  stmt                      = Update_stmt;

  return RC::SUCCESS;
}
