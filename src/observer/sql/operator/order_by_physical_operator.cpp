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
// Created by HuXin on 24-10-9.
//

#include "order_by_physical_operator.h"

OrderByPhysicalOperator::OrderByPhysicalOperator(vector<OrderBySqlNode> order_by, vector<Expression *> exprs)
    : order_by_(std::move(order_by)), exprs_(std::move(exprs))
{
  vector<Expression *> expressions;
  expressions.reserve(exprs_.size());
  for (auto &expr : exprs_) {
    expressions.push_back(expr);
  }
  tuple_.init(expressions);
}

RC OrderByPhysicalOperator::fetch_and_sort_tables()
{
  RC rc = RC::SUCCESS;

  vector<pair<vector<Value>, vector<Value>>> order_and_field_line;

  while (RC::SUCCESS == (rc = children_[0]->next())) {
    // 获取 order by 字段的 values
    vector<Value> order_by_line;
    for (auto &[expr, asc] : order_by_) {
      Value cell;
      rc = expr->get_value(*children_[0]->current_tuple(), cell);
      if (OB_FAIL(rc)) {
        return rc;
      }
      order_by_line.emplace_back(cell);
    }

    // 获取 select 字段的 values
    vector<Value> field_line;
    for (auto &expr : tuple_.exprs()) {
      Value cell;
      rc = expr->get_value(*children_[0]->current_tuple(), cell);
      if (OB_FAIL(rc)) {
        return rc;
      }
      field_line.emplace_back(cell);
    }

    order_and_field_line.emplace_back(order_by_line, field_line);
  }

  rc = RC::SUCCESS;

  // consider null
  auto cmp = [this](const pair<vector<Value>, vector<Value>> &cells_a,
                 const pair<vector<Value>, vector<Value>>    &cells_b) -> bool {
    auto  order_size   = order_by_.size();
    auto &order_line_a = cells_a.first;
    auto &order_line_b = cells_b.first;
    assert(order_line_a.size() == order_size);
    assert(order_line_b.size() == order_size);
    assert(order_by_.size() == order_size);

    for (size_t i = 0; i < order_size; i++) {
      auto a      = order_line_a[i];
      auto b      = order_line_b[i];
      auto result = a.compare(b);
      auto is_asc = order_by_[i].is_asc;
      if (result < 0) {
        // a < b
        return is_asc;
      } else if (result > 0) {
        // a > 0
        return !is_asc;
      }
    }

    // order_line_a == order_line_b
    return false;
  };

  sort(order_and_field_line.begin(), order_and_field_line.end(), cmp);
  for (auto &[_, value] : order_and_field_line) {
    values_.push_back(value);
  }

  it_ = values_.begin();
  return rc;
}

RC OrderByPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  if (children_.size() != 1) {
    return RC::INTERNAL;
  }
  rc = children_[0]->open(trx);
  if (OB_FAIL(rc)) {
    return rc;
  }
  rc = fetch_and_sort_tables();
  return rc;
}

RC OrderByPhysicalOperator::next()
{
  RC rc = RC::SUCCESS;
  if (it_ == values_.end()) {
    return RC::RECORD_EOF;
  }

  const vector<Value> &value = *it_;
  tuple_.set_cells(value);
  it_++;
  return rc;
}

RC OrderByPhysicalOperator::close() { return children_[0]->close(); }

Tuple *OrderByPhysicalOperator::current_tuple() { return &tuple_; }
