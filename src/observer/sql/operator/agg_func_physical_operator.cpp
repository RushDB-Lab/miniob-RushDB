// /* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
// miniob is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details. */

// //
// // Created by WangYunlai on 2021/6/9.
// //

#include "sql/operator/agg_func_physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field_meta.h"
#include "storage/record/record.h"
#include "storage/table/table.h"
#include "event/sql_debug.h"
#include "src/observer/sql/operator/aggfuncs/max_agg_func.h"
#include "src/observer/sql/operator/aggfuncs/min_agg_func.h"
#include "src/observer/sql/operator/aggfuncs/avg_agg_func.h"
#include "src/observer/sql/operator/aggfuncs/sum_agg_func.h"
#include "src/observer/sql/operator/aggfuncs/count_agg_func.h"
#include <cstddef>
#include <string>
#include <vector>

using namespace std;

RC AggFuncPhysicalOperator::open(Trx *trx)
{
  RC rc = table_->get_record_scanner(record_scanner_, trx, readonly_);
  tuple_.set_table(table_);
  int index = 0;
  for (auto aggs : agg_funcs) {
    switch (aggs.type) {
      case AGG_MAX: {
        auto temp = new max_agg_func();
        temp->init(aggs, table_, fields_[index].meta(), current_record_);
        agg_operators.push_back(temp);
      } break;
      case AGG_MIN: {
        auto temp = new min_agg_func();
        temp->init(aggs, table_, fields_[index].meta(), current_record_);
        agg_operators.push_back(temp);
      } break;
      case AGG_AVG: {
        auto temp = new avg_agg_func();
        temp->init(aggs, table_, fields_[index].meta(), current_record_);
        agg_operators.push_back(temp);
      } break;
      case AGG_SUM: {
        auto temp = new sum_agg_func();
        temp->init(aggs, table_, fields_[index].meta(), current_record_);
        agg_operators.push_back(temp);
      } break;
      case AGG_COUNT: {
        auto temp = new count_agg_func();
        temp->init(aggs, table_, nullptr, current_record_);
        agg_operators.push_back(temp);
      } break;
      default: return RC::FAILURE;
    }
    index++;
  }
  trx_ = trx;

  return rc;
}

RC AggFuncPhysicalOperator::next()
{
  if (!record_scanner_.has_next()) {
    return RC::RECORD_EOF;
  }
  RC rc = RC::SUCCESS;
  while (record_scanner_.has_next()) {
    bool filter_result = false;
    rc                 = record_scanner_.next(current_record_);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    tuple_.set_record(&current_record_);
    rc = filter(tuple_, filter_result);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    if (!filter_result)
      continue;
    // 确定了是我们想要的tuple
    for (auto agg : agg_operators) {
      agg->update(current_record_);
    }
  }
  // 把拿回来的value依次放入record
  std::vector<Value>       back_valus;
  std::vector<FieldExpr *> field_exprs;
  int                      i = 0, offset = 0;
  for (auto oper : agg_operators) {
    Value temp = oper->get_value();
    back_valus.push_back(temp);

    auto field_expr_temp = new FieldExpr(table_,
        new FieldMeta(fields_[i].field_name(), back_valus[i].attr_type(), offset, back_valus[i].length(), true));
    field_exprs.push_back(field_expr_temp);

    offset += back_valus[i].length();
    ++i;
  }
  Record back_record;
  make_record(back_valus.size(), back_valus.data(), back_record);
  current_record_ = back_record;
  tuple_.set_record(&current_record_);
  tuple_.set_fieldexper(field_exprs);
  tuple_.is_visited.assign(field_exprs.size(), false);
  return rc;
}

RC AggFuncPhysicalOperator::close() { return record_scanner_.close_scan(); }

Tuple *AggFuncPhysicalOperator::current_tuple()
{
  tuple_.set_record(&current_record_);
  return &tuple_;
}

string AggFuncPhysicalOperator::param() const { return table_->name(); }

void AggFuncPhysicalOperator::set_predicates(vector<unique_ptr<Expression>> &&exprs) { predicates_ = std::move(exprs); }

RC AggFuncPhysicalOperator::filter(RowTuple &tuple, bool &result)
{
  RC rc = RC::SUCCESS;

  std::vector<FieldExpr *> field_exprs;
  for (unique_ptr<Expression> &expr : predicates_) {
    auto k               = expr->name();
    auto field_expr_temp = new FieldExpr(table_, table_->table_meta().field(expr->name().c_str()));
    field_exprs.push_back(field_expr_temp);
  }
  tuple_.set_fieldexper(field_exprs);

  Value value;
  for (unique_ptr<Expression> &expr : predicates_) {
    rc = expr->get_value(tuple, value);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    bool tmp_result = value.get_boolean();
    if (!tmp_result) {
      result = false;
      return rc;
    }
  }

  result = true;
  return rc;
}

RC AggFuncPhysicalOperator::make_record(int value_num, const Value *values, Record &record)
{
  size_t record_size = 0;
  int    offset      = 0;

  for (int i = 0; i < value_num; i++) {
    record_size += values[i].length();
  }
  char *record_data = (char *)malloc(record_size);

  for (int i = 0; i < value_num; i++) {
    const Value &value = values[i];
    memcpy(record_data + offset, value.data(), values[i].length());
    offset += values[i].length();
  }
  record.set_data_owner(record_data, record_size);
  return RC::SUCCESS;
}

// /*SELECT count(*) FROM aggregation_func;
// - 4
// -- below are some requests executed before(partial) --
// -- init data
// CREATE TABLE aggregation_func(id int, num int, price float, addr char(4), birthday date);
// INSERT INTO aggregation_func VALUES (1, 18, 10.0, 'abc', '2020-01-01');
// INSERT INTO aggregation_func VALUES (2, 15, 20.0, 'abc', '2010-01-11');
// INSERT INTO aggregation_func VALUES (3, 12, 30.0, 'def', '2021-01-21');
// INSERT INTO aggregation_func VALUES (4, 15, 30.0, 'dei', '2021-01-31');
// ...*/