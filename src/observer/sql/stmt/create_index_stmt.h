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

#pragma once

#include <string>

#include "sql/stmt/stmt.h"
#include "storage/table/table_meta.h"
#include "sql/expr/expression.h"

struct CreateIndexSqlNode;
class Table;
class FieldMeta;

/**
 * @brief 创建索引的语句
 * @ingroup Statement
 */
class CreateIndexStmt : public Stmt
{
public:
  CreateIndexStmt(Table *table, IndexType index_type, const vector<FieldMeta> &field_meta,
      const std::string &index_name, bool unique)
      : table_(table), index_type_(index_type), field_meta_(field_meta), index_name_(index_name), unique_(unique)
  {}

  // 向量索引
  CreateIndexStmt(Table *table, IndexType index_type, const vector<FieldMeta> &field_meta,
      const std::string &index_name, NormalFunctionType distance_type, std::vector<int> options = {})
      : table_(table),
        index_type_(index_type),
        field_meta_(field_meta),
        index_name_(index_name),
        distance_type_(distance_type),
        options_(std::move(options))
  {}

  ~CreateIndexStmt() override = default;

  StmtType type() const override { return StmtType::CREATE_INDEX; }

  Table                   *table() const { return table_; }
  const vector<FieldMeta> &field_meta() const { return field_meta_; }
  const std::string       &index_name() const { return index_name_; }
  bool                     unique() const { return unique_; }
  IndexType                index_type() const { return index_type_; }
  NormalFunctionType       distance_type() const { return distance_type_; }
  const std::vector<int>  &options() const { return options_; }

public:
  static RC create(Db *db, const CreateIndexSqlNode &create_index, Stmt *&stmt);

private:
  Table             *table_ = nullptr;
  IndexType          index_type_;
  vector<FieldMeta>  field_meta_;
  std::string        index_name_;
  bool               unique_ = false;
  NormalFunctionType distance_type_;
  std::vector<int>   options_;
};
