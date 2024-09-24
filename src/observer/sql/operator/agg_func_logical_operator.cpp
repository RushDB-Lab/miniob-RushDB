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
// // Created by Wangyunlai on 2022/12/15
// //

#include "sql/operator/agg_func_logical_operator.h"
#include "sql/stmt/filter_stmt.h"

AggFuncLogicalOperator::AggFuncLogicalOperator(
    Table *table, const std::vector<Field> &fields, std::vector<Agg_Func> &agg_func_, bool readonly)
    : table_(table), fields_(fields), readonly_(readonly), agg_funcs(agg_func_)
{}

void AggFuncLogicalOperator::set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs)
{
  predicates_ = std::move(exprs);
}
void AggFuncLogicalOperator::creat_predicates_(FilterStmt *filter_stmt)
{

  const std::vector<FilterUnit *> &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    std::unique_ptr<Expression> left(filter_obj_left.is_attr
                                         ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                         : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    std::unique_ptr<Expression> right(filter_obj_right.is_attr
                                          ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                          : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    if (filter_obj_left.is_attr) {
      cmp_expr->set_name(filter_obj_left.field.field_name());
    } else {
      cmp_expr->set_name(filter_obj_right.field.field_name());
    }
    predicates_.emplace_back(cmp_expr);
  }
}