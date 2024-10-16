/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
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

#include <utility>

#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "storage/table/view.h"
#include "sql/stmt/insert_stmt.h"

InsertStmt::InsertStmt(BaseTable *table, std::vector<std::vector<Value>> values_list)
    : table_(table), values_list_(std::move(values_list))
{}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values_list.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values_list.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  auto table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (table->type() == TableType::View) {
    if (!table->is_mutable()) {
      LOG_ERROR("The target table %s of the INSERT is not insertable-into", table->name());
      return RC::READ_ONLY_VIEW_INSERT_ERROR;
    }
    auto view = dynamic_cast<View *>(table);
    if (view->has_join()) {
      LOG_ERROR("Can not insert into join view '%s.%s' without fields list", db->name(), table->name());
      return RC::JOIN_VIEW_INSERT_ERROR;
    }
  }

  // check the fields are mutable
  // 有表达式的列整个表都不能插入，但是可以删除更新非表达式列
  const TableMeta &table_meta  = table->table_meta();
  auto             field_metas = table_meta.field_metas();
  for (auto &field_meta : *field_metas) {
    if (!field_meta.is_mutable()) {
      LOG_ERROR("Column '%s' is not insertable", field_meta.name());
      return RC::EXPRESSION_FIELD_NOT_INSERTABLE;
    }
  }

  std::vector<std::vector<Value>> values_list = inserts.values_list;
  const int                       field_num   = table_meta.field_num() - table_meta.sys_field_num();

  // check the fields number
  for (auto &value_list : inserts.values_list) {
    const int value_num = static_cast<int>(value_list.size());
    if (inserts.attr_names.empty()) {
      if (field_num != value_num) {
        LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
        return RC::SCHEMA_FIELD_MISSING;
      }
    } else if (field_num < value_num || inserts.attr_names.size() != value_num) {
      LOG_WARN("schema mismatch. attr num=%d, value num=%d, field num in schema=%d", inserts.attr_names.size(), value_num, field_num);
      return RC::INVALID_ARGUMENT;
    }
  }

  if (!inserts.attr_names.empty()) {
    // 在物理算子执行阶段检查值的可为空性
    // 预处理索引
    std::unordered_set<int> field_ids;
    std::vector<int>        index(inserts.attr_names.size(), -1);
    for (int i = 0; i < inserts.attr_names.size(); ++i) {
      auto &attr_name  = inserts.attr_names[i];
      auto  field_meta = table_meta.field(attr_name.c_str());
      if (field_meta != nullptr) {
        // 出现两次同名列
        if (field_ids.count(field_meta->field_id())) {
          LOG_ERROR("Column '%s' specified twice", attr_name.c_str());
          return RC::INVALID_ARGUMENT;
        }
        index[i] = field_meta->field_id();
        field_ids.emplace(index[i]);
      } else {
        LOG_WARN("Field does not exist. db=%s, table_name=%s, field_name=%s",
                  db->name(), table_name, attr_name.c_str());
        return RC::SCHEMA_FIELD_NOT_EXIST;
      }
    }

    for (auto &value_list : values_list) {
      std::vector<Value> values(field_num);
      for (auto &value : values) {
        value.set_null();
      }
      for (int k = 0; k < value_list.size(); ++k) {
        values[index[k]] = value_list[k];
      }
      value_list = std::move(values);
    }
  }

  // everything alright
  stmt = new InsertStmt(table, std::move(values_list));
  return RC::SUCCESS;
}
