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
// Created by WangYunlai on 2022/6/27.
//

#include "common/log/log.h"
#include "sql/expr/tuple.h"
#include "sql/operator/predicate_physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/parser/value.h"
#include "storage/record/record.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/field/field.h"

PredicatePhysicalOperator::PredicatePhysicalOperator(
    std::unique_ptr<Expression> expr, std::vector<std::unique_ptr<PhysicalOperator>> &child_select_physical_operator)
    : expression_(std::move(expr)), child_select_physical_operator_(std::move(child_select_physical_operator))
{
  ASSERT(expression_->value_type() == BOOLEANS, "predicate's expression should be BOOLEAN type");
}

RC PredicatePhysicalOperator::open(Trx *trx)
{
  if (children_.size() != 1) {
    LOG_WARN("predicate operator must has one child");
    return RC::INTERNAL;
  }
  // 获取比较类型
  comp = static_cast<ComparisonExpr *>(expression_.get())->comp();
  if (child_select_physical_operator_.size() == 0) {
    return children_[0]->open(trx);
  } else {
    RC rc = children_[0]->open(trx);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    // 有子查询，就先打开子查询

    for (auto &child : child_select_physical_operator_) {
      RC rc = child->open(trx);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      while (child->next() == RC::SUCCESS) {
        Tuple *tuple = child->current_tuple();
        if (tuple == nullptr) {
          return RC::INTERNAL;
        }
        Value cell;
        tuple->cell_at(0, cell);
        // 将其放入合适的value数组里
        if (comp == in) {
          in_values_.push_back(cell);
        } else if (comp == not_in) {
          not_in_values_.push_back(cell);
        } else if (comp == NO_OP) {
          return RC::FAILURE;
        } else {
          other_values.push_back(cell);
        }
      }
      child->close();

      return RC::SUCCESS;
    }
  }
  return RC::SUCCESS;
}

RC PredicatePhysicalOperator::next()
{
  RC                rc   = RC::SUCCESS;
  PhysicalOperator *oper = children_.front().get();

  while (RC::SUCCESS == (rc = oper->next())) {
    Tuple *tuple = oper->current_tuple();
    if (nullptr == tuple) {
      rc = RC::INTERNAL;
      LOG_WARN("failed to get tuple from operator");
      break;
    }

    Value value;
    if (comp == in) {
      rc = cheak_in_inValue(value, tuple);
      if (value.get_boolean())
        return RC::SUCCESS;
    } else if (comp == not_in) {
      rc = cheak_in_Not_inValue(value, tuple);
      if (value.get_boolean())
        return RC::SUCCESS;
    } else if (comp == in_EQUAL_TO || comp == in_GREAT_EQUAL || comp == in_GREAT_THAN || comp == in_LESS_EQUAL ||
               comp == in_LESS_THAN || comp == in_NOT_EQUAL) {
      rc = cheak_with_other_Value(value, tuple);
      if (value.get_boolean())
        return RC::SUCCESS;
    } else {
      rc = expression_->get_value(*tuple, value);
      if (rc != RC::SUCCESS) {
        return rc;
      }

      if (value.get_boolean()) {
        return rc;
      }
    }
  }
  return rc;
}

RC PredicatePhysicalOperator::close()
{
  children_[0]->close();
  return RC::SUCCESS;
}

Tuple *PredicatePhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }

RC PredicatePhysicalOperator::cheak_in_inValue(Value &value, Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  if (in_values_.size() == 0) {
    value.set_boolean(false);
    return RC::SUCCESS;
  }
  bool pass = false;
  for (int i = 0; i < in_values_.size(); i++) {
    expression_->set_value(&in_values_[i]);
    //
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS)
      return rc;
    if (value.get_boolean())  // 存在合适
    {
      pass = true;
      break;
    }
    pass = false;
  }
  value.set_boolean(pass);
  return RC::SUCCESS;
}

RC PredicatePhysicalOperator::cheak_in_Not_inValue(Value &value, Tuple *tuple)
{
  RC rc = RC::SUCCESS;
  if (not_in_values_.size() == 0) {
    value.set_boolean(true);
    return RC::SUCCESS;
  }
  bool pass = false;
  for (int i = 0; i < not_in_values_.size(); i++) {
    expression_->set_value(&not_in_values_[i]);
    //
    rc = expression_->get_value(*tuple, value);
    if (rc != RC::SUCCESS)
      return rc;
    if (!value.get_boolean())  // 存在不应该存在的合适
    {
      pass = false;
      break;
    }
    pass = true;
  }
  value.set_boolean(pass);
  return RC::SUCCESS;
}

RC PredicatePhysicalOperator::cheak_with_other_Value(Value &value, Tuple *tuple)
{
  if (other_values.size() > 1)
    return RC::FAILURE;
  expression_->set_value(&other_values[0]);
  RC rc = expression_->get_value(*tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (value.get_boolean()) {
    return rc;
  }
  return RC::SUCCESS;
}