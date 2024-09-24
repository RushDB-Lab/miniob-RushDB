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
// Created by Wangyunlai on 2022/6/5.
//

#pragma once

#include <vector>
#include <memory>

#include "common/rc.h"
#include "sql/stmt/stmt.h"
#include "storage/field/field.h"

class FieldMeta;
class FilterStmt;
class Db;
class Table;

struct Agg_Func
{
  Agg_Func() = default;
  Agg_Func(Agg_Type type_, RelAttrSqlNode attributes_) : type(type_) { attributes = attributes_; };
  Agg_Type       type = AGG_UNDEFIND;
  RelAttrSqlNode attributes;
};
struct orderby
{
  orderby() = default;
  orderby(OrderBy other)
  {
    type       = other.type;
    attributes = other.attributes;
  }
  orderby_type     type = UNDEFINED_ORDER_TYPE;
  RelAttrSqlNode   attributes;
  const FieldMeta *field_meta = nullptr;
};

/**
 * @brief 表示select语句
 * @ingroup Statement
 */
class SelectStmt : public Stmt
{
public:
  SelectStmt() = default;
  ~SelectStmt() override;

  StmtType type() const override { return StmtType::SELECT; }

public:
  static RC create(Db *db, const SelectSqlNode &select_sql, Stmt *&stmt);
  static RC get_orderby_mate(const std::unordered_map<std::string, Table *> &table_map_, std::vector<OrderBy> OrderBys_,
      std::vector<orderby> &orderbys_);

public:
  const std::vector<Table *> &tables() const { return tables_; }
  const std::vector<Field>   &query_fields() const { return query_fields_; }
  FilterStmt                 *filter_stmt() const { return filter_stmt_; }
  std::vector<Agg_Func>      &agg_func() { return agg_funcs; }
  auto                        get_OrderBy() { return OrderBys; }

private:
  std::vector<Field>    query_fields_;
  std::vector<Table *>  tables_;
  FilterStmt           *filter_stmt_ = nullptr;
  std::vector<Agg_Func> agg_funcs;
  std::vector<orderby>  OrderBys;
};
