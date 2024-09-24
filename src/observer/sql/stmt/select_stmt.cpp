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
#include "common/rc.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "storage/db/db.h"
#include "storage/field/field.h"
#include "storage/field/field_meta.h"
#include "storage/table/table.h"
#include <algorithm>
#include <cstring>
#include <iterator>
#include <vector>

SelectStmt::~SelectStmt()
{
  if (nullptr != filter_stmt_) {
    delete filter_stmt_;
    filter_stmt_ = nullptr;
  }
}
// 判断是不是like匹配
bool is_like(const SelectSqlNode &select_sql)
{
  int  size = select_sql.conditions.size();
  auto cond = select_sql.conditions;
  if (size == 0 || size > 2) {
    return false;
  } else {
    return cond[0].like.size() != 0 || cond[0].not_like.size() != 0;
  }
}

static void wildcard_fields(Table *table, std::vector<Field> &field_metas)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    field_metas.push_back(Field(table, table_meta.field(i)));
  }
}

RC SelectStmt::create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt)
{
  if (nullptr == db) {
    LOG_WARN("invalid argument. db is null");
    return RC::INVALID_ARGUMENT;
  }
  // 把inner里的数据倒出来
  auto ptr = const_cast<SelectSqlNode *>(&select_sql);
  reverse(ptr->inner.table_name.begin(), ptr->inner.table_name.end());
  ptr->relations.insert(ptr->relations.end(), select_sql.inner.table_name.begin(), select_sql.inner.table_name.end());
  ptr->conditions.insert(ptr->conditions.end(), select_sql.inner.conditions.begin(), select_sql.inner.conditions.end());

  //  collect tables in `from` statement
  std::vector<Table *>                     tables;
  std::unordered_map<std::string, Table *> table_map;
  for (size_t i = 0; i < select_sql.relations.size(); i++) {
    const char *table_name = select_sql.relations[i].c_str();
    if (nullptr == table_name) {
      LOG_WARN("invalid argument. relation name is null. index=%d", i);
      return RC::INVALID_ARGUMENT;
    }

    Table *table = db->find_table(table_name);
    if (nullptr == table) {
      LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables.push_back(table);
    table_map[table_name] = table;
  }

  // collect query fields in `select` statement
  std::vector<Field> query_fields;
  std::reverse(ptr->attributes.begin(), ptr->attributes.end());

  // cheak order by's field is exist
  std::vector<orderby> OrderBys_;
  RC                   rc = get_orderby_mate(table_map, select_sql.order_bys, OrderBys_);
  if (rc != RC::SUCCESS) {
    LOG_WARN("The order by filed has error");
    return rc;
  }

  // 处理聚合函数
  bool                  is_attr     = false;
  bool                  is_agg_func = false;
  std::vector<Agg_Func> agg_funcs;
  for (auto RelAttr_node : select_sql.attributes) {
    if (RelAttr_node.type != AGG_UNDEFIND && is_attr == false) {
      is_agg_func = true;
      Agg_Func temp(RelAttr_node.type, RelAttr_node);
      agg_funcs.push_back(temp);
      continue;
    } else if (RelAttr_node.type != AGG_UNDEFIND && is_attr == true) {
      return RC::FAILURE;
    } else if (is_agg_func) {
      return RC::FAILURE;
    } else if (!is_agg_func) {
      is_attr = true;
    }
  }

  int attributes_size = ptr->attributes.size();
  if (agg_funcs.size() != 0) {
    int offset = 0;
    for (auto rel : agg_funcs) {
      // 先判断列名是否存在
      // 先处理count(*)的情况
      if (0 == strcmp(rel.attributes.attribute_name.c_str(), "*") && rel.type != AGG_COUNT) {
        return RC::FAILURE;
      } else if (rel.type == AGG_COUNT) {
        if (0 != strcmp(rel.attributes.attribute_name.c_str(), "*")) {
          const FieldMeta *old = tables[0]->table_meta().field(rel.attributes.attribute_name.c_str());
          if (old == nullptr)
            return RC::FAILURE;
        }
        Field agg_filed(tables[0], new FieldMeta(rel.attributes.attribute_name.c_str(), INTS, offset, 4, true));
        offset += 4;  // 一个count偏移4个字节
        query_fields.push_back(agg_filed);
      } else {
        const FieldMeta *old = tables[0]->table_meta().field(rel.attributes.attribute_name.c_str());
        if (old == nullptr)
          return RC::FAILURE;
        Field agg_filed(tables[0],
            new FieldMeta(rel.attributes.attribute_name.c_str(), old->attr_type(), offset, old->len(), true));
        offset += old->len();
        query_fields.push_back(agg_filed);
      }
    }
    goto end;
  }
  // 处理select原本的field处理
  for (int i = 0; i < attributes_size; i++) {
    const RelAttrSqlNode &relation_attr = select_sql.attributes[i];
    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      for (Table *table : tables) {
        wildcard_fields(table, query_fields);
      }

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        if (0 != strcmp(field_name, "*")) {
          LOG_WARN("invalid field name while table is *. attr=%s", field_name);
          return RC::SCHEMA_FIELD_MISSING;
        }
        for (Table *table : tables) {
          wildcard_fields(table, query_fields);
        }
      } else {
        auto iter = table_map.find(table_name);
        if (iter == table_map.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          wildcard_fields(table, query_fields);
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }

          query_fields.push_back(Field(table, field_meta));
        }
      }
    } else {
      if (tables.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = tables[0];
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s.%s", db->name(), table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      query_fields.push_back(Field(table, field_meta));
    }
  }

  LOG_INFO("got %d tables in from stmt and %d fields in query stmt", tables.size(), query_fields.size());
end:
  Table *default_table = nullptr;
  if (tables.size() == 1) {
    default_table = tables[0];
  }

  // create filter statement in `where` statement

  FilterStmt *filter_stmt = nullptr;
  rc                      = FilterStmt::create(db,
      default_table,
      &table_map,
      select_sql.conditions.data(),
      static_cast<int>(select_sql.conditions.size()),
      filter_stmt,
      is_like(select_sql));
  if (rc != RC::SUCCESS) {
    LOG_WARN("cannot construct filter stmt");
    return rc;
  }

  // everything alright
  SelectStmt *select_stmt = new SelectStmt();
  // TODO add expression copy
  select_stmt->tables_.swap(tables);
  select_stmt->query_fields_.swap(query_fields);
  select_stmt->filter_stmt_ = filter_stmt;
  select_stmt->agg_funcs    = agg_funcs;
  select_stmt->OrderBys     = OrderBys_;
  stmt                      = select_stmt;
  return RC::SUCCESS;
}

// 检查order by的field是否存在
RC SelectStmt::get_orderby_mate(const std::unordered_map<std::string, Table *> &table_map_,
    std::vector<OrderBy> OrderBys_, std::vector<orderby> &orderbys_)
{
  for (int i = 0; i < OrderBys_.size(); i++) {
    orderby               temp(OrderBys_[i]);
    const RelAttrSqlNode &relation_attr = temp.attributes;
    orderbys_.push_back(temp);

    if (common::is_blank(relation_attr.relation_name.c_str()) &&
        0 == strcmp(relation_attr.attribute_name.c_str(), "*")) {
      LOG_WARN("can not order by the field \"*\"");
      return RC::FAILURE;

    } else if (!common::is_blank(relation_attr.relation_name.c_str())) {
      const char *table_name = relation_attr.relation_name.c_str();
      const char *field_name = relation_attr.attribute_name.c_str();

      if (0 == strcmp(table_name, "*")) {
        LOG_WARN("can not order by the field \"*\"");
        return RC::FAILURE;
      } else {
        auto iter = table_map_.find(table_name);
        if (iter == table_map_.end()) {
          LOG_WARN("no such table in from list: %s", table_name);
          return RC::SCHEMA_FIELD_MISSING;
        }

        Table *table = iter->second;
        if (0 == strcmp(field_name, "*")) {
          LOG_WARN("can not order by the field \"*\"");
          return RC::FAILURE;
        } else {
          const FieldMeta *field_meta = table->table_meta().field(field_name);
          if (nullptr == field_meta) {
            LOG_WARN("no such field. field=%s.%s", table->name(), field_name);
            return RC::SCHEMA_FIELD_MISSING;
          }
          // 获得了正确的field_meta
          orderbys_[i].field_meta = field_meta;
        }
      }
    } else {
      if (table_map_.size() != 1) {
        LOG_WARN("invalid. I do not know the attr's table. attr=%s", relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }

      Table           *table      = table_map_.begin()->second;
      const FieldMeta *field_meta = table->table_meta().field(relation_attr.attribute_name.c_str());
      if (nullptr == field_meta) {
        LOG_WARN("no such field. field=%s.%s", table->name(), relation_attr.attribute_name.c_str());
        return RC::SCHEMA_FIELD_MISSING;
      }
      orderbys_[i].attributes.relation_name = table_map_.begin()->first;
      orderbys_[i].field_meta               = field_meta;
    }
  }
  return RC::SUCCESS;
}