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
// Created by Wangyunlai on 2023/4/25.
//

#include "sql/stmt/create_index_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

using namespace std;
using namespace common;

RC CreateIndexStmt::create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt)
{
  stmt = nullptr;

  const char *table_name = create_index.relation_name.c_str();
  if (is_blank(table_name) || is_blank(create_index.index_name.c_str())) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, index name=%s",
        db, table_name, create_index.index_name.c_str());
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  BaseTable *base_table = db->find_table(table_name);
  if (nullptr == base_table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  if (base_table->type() != TableType::Table) {
    LOG_WARN("table %s is not BASE TABLE. db=%s",
             table_name, db->name());
    return RC::CREATE_INDEX_ON_NON_TABLE_TYPE;
  }

  Table            *table = static_cast<Table *>(base_table);
  vector<FieldMeta> field_metas;
  RC                rc = table->table_meta().get_field_metas(create_index.attribute_name, field_metas);
  if (OB_FAIL(rc)) {
    LOG_WARN("no such field in table. db=%s, table=%s",
             db->name(), table_name);
    return rc;
  }

  Index *index = table->find_index(create_index.index_name.c_str());
  if (nullptr != index) {
    LOG_WARN("index with name(%s) already exists. table name=%s", create_index.index_name.c_str(), table_name);
    return RC::SCHEMA_INDEX_NAME_REPEAT;
  }

  auto config = create_index.vector_index_config;

  auto index_type = config.index_type;
  if (index_type == IndexType::BPlusTreeIndex) {
    stmt = new CreateIndexStmt(table, index_type, field_metas, create_index.index_name, create_index.unique);
  } else if (index_type == IndexType::VectorIVFFlatIndex) {
    // 解析距离度量方法，后续单独提取出去
    auto               distance_type_str = common::str_to_lower(config.distance_fn);
    NormalFunctionType distance_type;
    if (distance_type_str == "l2_distance") {
      distance_type = NormalFunctionType::L2_DISTANCE;
    } else if (distance_type_str == "inner_product") {
      distance_type = NormalFunctionType::INNER_PRODUCT;
    } else if (distance_type_str == "cosine_distance") {
      distance_type = NormalFunctionType::COSINE_DISTANCE;
    } else {
      return RC::UNSUPPORTED;
    }

    // 没有参数，使用默认参数
    if (config.lists.attr_type() == AttrType::UNDEFINED && config.probes.attr_type() == AttrType::UNDEFINED) {
      stmt = new CreateIndexStmt(table, index_type, field_metas, create_index.index_name, distance_type);
    } else if (config.lists.attr_type() == AttrType::INTS && config.probes.attr_type() == AttrType::INTS) {
      std::vector<int> options(2);
      options[0] = config.lists.get_int();
      options[1] = config.probes.get_int();
      stmt       = new CreateIndexStmt(
          table, index_type, field_metas, create_index.index_name, distance_type, std::move(options));
    } else {
      return RC::INVALID_ARGUMENT;
    }
  }

  return RC::SUCCESS;
}
