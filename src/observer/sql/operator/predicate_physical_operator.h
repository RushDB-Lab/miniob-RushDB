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

#pragma once

#include <memory>
#include <vector>
#include "sql/operator/physical_operator.h"
#include "sql/expr/expression.h"
#include "sql/parser/value.h"

class FilterStmt;

/**
 * @brief 过滤/谓词物理算子
 * @ingroup PhysicalOperator
 */
class PredicatePhysicalOperator : public PhysicalOperator
{
public:
  PredicatePhysicalOperator(
      std::unique_ptr<Expression> expr, std::vector<std::unique_ptr<PhysicalOperator>> &child_select_physical_operator);

  virtual ~PredicatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::PREDICATE; }
  void                 set_child_select_physical_operator_(
                      std::vector<std::unique_ptr<PhysicalOperator>> &child_select_physical_operator_)
  {
    PredicatePhysicalOperator ::child_select_physical_operator_ = std::move(child_select_physical_operator_);
  }
  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  RC     cheak_in_inValue(Value &value, Tuple *tuple);
  RC     cheak_in_Not_inValue(Value &value, Tuple *tuple);
  RC     cheak_with_other_Value(Value &value, Tuple *tuple);
  Tuple *current_tuple() override;

private:
  std::unique_ptr<Expression>                    expression_;
  CompOp                                         comp;
  std::vector<std::unique_ptr<PhysicalOperator>> child_select_physical_operator_;
  std::vector<bool>                              in_or_not;
  std::vector<Value>                             in_values_;
  std::vector<Value>                             not_in_values_;
  std::vector<Value>                             other_values;
};
