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
// Created by Wangyunlai on 2022/12/07.
//

#pragma once

#include "sql/operator/logical_operator.h"
#include "sql/expr/expression.h"

/**
 * @brief 谓词/过滤逻辑算子
 * @ingroup LogicalOperator
 */
class PredicateLogicalOperator : public LogicalOperator
{
public:
  PredicateLogicalOperator(std::unique_ptr<Expression> expression);
  virtual ~PredicateLogicalOperator() = default;
  void set_logical_child_operator(std::vector<std::unique_ptr<LogicalOperator>> child_logical_operator)
  {
    child_select_logical_operator_ = std::move(child_logical_operator);
  }
  std::vector<std::unique_ptr<LogicalOperator>> get_child_select_logical_operator_()
  {
    return std::move(child_select_logical_operator_);
  }
  LogicalOperatorType type() const override { return LogicalOperatorType::PREDICATE; }

private:
  std::vector<std::unique_ptr<LogicalOperator>> child_select_logical_operator_;
};
