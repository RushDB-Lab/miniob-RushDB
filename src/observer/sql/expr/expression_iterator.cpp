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
// Created by Wangyunlai on 2024/05/30.
//

#include "sql/expr/expression_iterator.h"

#include <memory>
#include "sql/expr/expression.h"
#include "common/log/log.h"

using namespace std;

RC ExpressionIterator::iterate_child_expr(Expression &expr, const function<RC(unique_ptr<Expression> &)> &callback)
{
  RC rc = RC::SUCCESS;

  switch (expr.type()) {
    case ExprType::CAST: {
      auto &cast_expr = dynamic_cast<CastExpr &>(expr);
      rc              = callback(cast_expr.child());
    } break;

    case ExprType::COMPARISON: {
      auto &comparison_expr = dynamic_cast<ComparisonExpr &>(expr);
      rc                    = callback(comparison_expr.left());
      if (OB_SUCC(rc)) {
        rc = callback(comparison_expr.right());
      } else {
        return rc;
      }
    } break;

    case ExprType::CONJUNCTION: {
      auto &conjunction_expr = dynamic_cast<ConjunctionExpr &>(expr);
      for (auto &child : conjunction_expr.children()) {
        rc = callback(child);
        if (OB_FAIL(rc)) {
          break;
        }
      }
    } break;

    case ExprType::ARITHMETIC: {
      auto &arithmetic_expr = dynamic_cast<ArithmeticExpr &>(expr);
      rc                    = callback(arithmetic_expr.left());
      if (OB_SUCC(rc) && arithmetic_expr.right()) {
        rc = callback(arithmetic_expr.right());
      }
    } break;

    case ExprType::AGGREGATION: {
      auto &aggregate_expr = dynamic_cast<AggregateFunctionExpr &>(expr);
      rc                   = callback(aggregate_expr.child());
    } break;

    case ExprType::NORMAL_FUNCTION: {
      auto &normal_function_expr = dynamic_cast<NormalFunctionExpr &>(expr);
      for (auto &child_expr : normal_function_expr.args()) {
        rc = callback(child_expr);
      }
    } break;

    case ExprType::NONE:
    case ExprType::STAR:
    case ExprType::UNBOUND_FIELD:
    case ExprType::FIELD:
    case ExprType::VALUE: {
      // Do nothing
    } break;

    default: {
      ASSERT(false, "Unknown expression type");
    }
  }

  return rc;
}

RC ExpressionIterator::condition_iterate_expr(std::unique_ptr<Expression> &expr)
{
  RC rc = RC::SUCCESS;

  switch (expr->type()) {
    case ExprType::CAST: {

    } break;

    case ExprType::COMPARISON: {
      auto *comp_expr = dynamic_cast<ComparisonExpr *>(expr.get());
      auto &left      = comp_expr->left();
      auto &right     = comp_expr->right();

      if (right->type() == ExprType::EXPRLIST) {
        if (comp_expr->comp() != IN_OP && comp_expr->comp() != NOT_IN_OP) {
          return RC::UNSUPPORTED;
        }
      }

      if (left->value_type() != AttrType::NULLS && right->value_type() != AttrType::NULLS) {
        if (left->value_type() != right->value_type()) {
          auto left_to_right_cost = Value::implicit_cast_cost(left->value_type(), right->value_type());
          auto right_to_left_cost = Value::implicit_cast_cost(right->value_type(), left->value_type());

          if (right->type() == ExprType::SUBQUERY || right->type() == ExprType::EXPRLIST ||
              left->type() == ExprType::SUBQUERY || left->type() == ExprType::EXPRLIST) {
            // 暂时在这里不做处理
            return RC::SUCCESS;
          } else if (left_to_right_cost <= right_to_left_cost && left_to_right_cost != INT32_MAX) {
            ExprType left_type = left->type();
            auto     cast_expr = make_unique<CastExpr>(std::move(left), right->value_type());

            if (left_type == ExprType::VALUE) {
              Value left_val;
              rc = cast_expr->try_get_value(left_val);
              if (OB_FAIL(rc)) {
                LOG_WARN("failed to get value from left child", strrc(rc));
                return rc;
              }
              left = make_unique<ValueExpr>(left_val);
            } else {
              left = std::move(cast_expr);
            }
          } else if (right_to_left_cost < left_to_right_cost && right_to_left_cost != INT32_MAX) {
            ExprType right_type = right->type();
            auto     cast_expr  = make_unique<CastExpr>(std::move(right), left->value_type());

            if (right_type == ExprType::VALUE) {
              Value right_val;
              rc = cast_expr->try_get_value(right_val);
              if (OB_FAIL(rc)) {
                LOG_WARN("failed to get value from right child", strrc(rc));
                return rc;
              }
              right = make_unique<ValueExpr>(right_val);
            } else {
              right = std::move(cast_expr);
            }
          } else {
            rc = RC::UNSUPPORTED;
            LOG_WARN("unsupported cast from %s to %s",
                         attr_type_to_string(left->value_type()),
                         attr_type_to_string(right->value_type()));
            return rc;
          }
        }
      }
    } break;

    case ExprType::CONJUNCTION: {
      auto conjunction_expr = dynamic_cast<ConjunctionExpr *>(expr.get());
      for (auto &child : conjunction_expr->children()) {
        rc = condition_iterate_expr(child);
        if (OB_FAIL(rc)) {
          break;
        }
      }
    } break;

    case ExprType::ARITHMETIC:
    case ExprType::AGGREGATION:
    case ExprType::NORMAL_FUNCTION:
    case ExprType::NONE:
    case ExprType::STAR:
    case ExprType::UNBOUND_FIELD:
    case ExprType::FIELD:
    case ExprType::VALUE: {
      // Do nothing
    } break;

    default: {
      ASSERT(false, "Unknown expression type");
    }
  }

  return rc;
}

RC ExpressionIterator::having_condition_iterate_expr(
    std::unique_ptr<Expression> &expr, vector<Expression *> &bound_expressions)
{
  RC rc = RC::SUCCESS;

  switch (expr->type()) {
    case ExprType::COMPARISON: {
      auto *comp_expr = dynamic_cast<ComparisonExpr *>(expr.get());
      auto &left      = comp_expr->left();
      auto &right     = comp_expr->right();
      rc              = having_condition_iterate_expr(left, bound_expressions);
      if (OB_FAIL(rc)) {
        break;
      }
      rc = having_condition_iterate_expr(right, bound_expressions);
      if (OB_FAIL(rc)) {
        break;
      }

    } break;

    case ExprType::CONJUNCTION: {
      auto conjunction_expr = dynamic_cast<ConjunctionExpr *>(expr.get());
      for (auto &child : conjunction_expr->children()) {
        rc = having_condition_iterate_expr(child, bound_expressions);
        if (OB_FAIL(rc)) {
          break;
        }
      }
    } break;
    case ExprType::AGGREGATION: {
      bound_expressions.push_back(expr.get());
    } break;

    case ExprType::CAST:
    case ExprType::ARITHMETIC:
    case ExprType::NORMAL_FUNCTION:
    case ExprType::NONE:
    case ExprType::STAR:
    case ExprType::UNBOUND_FIELD:
    case ExprType::FIELD:
    case ExprType::VALUE: {
      // Do nothing
    } break;

    default: {
      ASSERT(false, "Unknown expression type");
    }
  }

  return rc;
}
