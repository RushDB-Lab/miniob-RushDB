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
// Created by Wangyunlai on 2022/07/05.
//

#include "sql/expr/expression.h"
#include "sql/expr/tuple.h"
#include "sql/expr/arithmetic_operator.hpp"

#include "sql/stmt/select_stmt.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/physical_operator.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "common/lang/defer.h"

using namespace std;

RC FieldExpr::get_value(const Tuple &tuple, Value &value)
{
  return tuple.find_cell(TupleCellSpec(table_name(), field_name()), value);
}

bool FieldExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::FIELD) {
    return false;
  }
  const auto &other_field_expr = static_cast<const FieldExpr &>(other);
  return table_name() == other_field_expr.table_name() && field_name() == other_field_expr.field_name();
}

// TODO: 在进行表达式计算时，`chunk` 包含了所有列，因此可以通过 `field_id` 获取到对应列。
// 后续可以优化成在 `FieldExpr` 中存储 `chunk` 中某列的位置信息。
RC FieldExpr::get_column(Chunk &chunk, Column &column)
{
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    column.reference(chunk.column(field().meta()->field_id()));
  }
  return RC::SUCCESS;
}

bool ValueExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != ExprType::VALUE) {
    return false;
  }
  const auto &other_value_expr = static_cast<const ValueExpr &>(other);
  return value_.compare(other_value_expr.get_value()) == 0;
}

RC ValueExpr::get_value(const Tuple &tuple, Value &value)
{
  value = value_;
  return RC::SUCCESS;
}

RC ValueExpr::get_column(Chunk &chunk, Column &column)
{
  column.init(value_);
  return RC::SUCCESS;
}

/////////////////////////////////////////////////////////////////////////////////
CastExpr::CastExpr(unique_ptr<Expression> child, AttrType cast_type) : child_(std::move(child)), cast_type_(cast_type)
{}

CastExpr::~CastExpr() {}

RC CastExpr::cast(const Value &value, Value &cast_value) const
{
  RC rc = RC::SUCCESS;
  if (this->value_type() == value.attr_type()) {
    cast_value = value;
    return rc;
  }
  rc = Value::cast_to(value, cast_type_, cast_value);
  return rc;
}

RC CastExpr::get_value(const Tuple &tuple, Value &result)
{
  Value value;
  RC    rc = child_->get_value(tuple, value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

RC CastExpr::try_get_value(Value &result) const
{
  Value value;
  RC    rc = child_->try_get_value(value);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  return cast(value, result);
}

////////////////////////////////////////////////////////////////////////////////

ComparisonExpr::ComparisonExpr(CompOp comp, Expression *left, Expression *right)
    : comp_(comp), left_(std::unique_ptr<Expression>(left)), right_(std::unique_ptr<Expression>(right))
{}

ComparisonExpr::~ComparisonExpr() = default;

RC ComparisonExpr::compare_value(const Value &left, const Value &right, bool &result) const
{
  if (comp_ == OP_IS) {
    if (right.attr_type() != AttrType::NULLS) {
      return RC::NOT_NULL_AFTER_IS;
    }
    result = left.is_null();
    return RC::SUCCESS;
  }
  if (comp_ == OP_IS_NOT) {
    if (right.attr_type() != AttrType::NULLS) {
      return RC::NOT_NULL_AFTER_IS;
    }
    result = !left.is_null();
    return RC::SUCCESS;
  }
  if (left.is_null() || right.is_null()) {
    result = false;
    return RC::SUCCESS;
  }

  RC rc = RC::SUCCESS;

  if (comp_ == LIKE_OP || comp_ == NOT_LIKE_OP) {
    ASSERT(left.is_str() && right.is_str(), "LIKE ONLY SUPPORT STRING TYPE!");
    result = comp_ == LIKE_OP ? left.LIKE(right) : !left.LIKE(right);
    return rc;
  }

  int cmp_result = left.compare(right);
  result         = false;
  switch (comp_) {
    case EQUAL_TO: {
      result = (0 == cmp_result);
    } break;
    case LESS_EQUAL: {
      result = (cmp_result <= 0);
    } break;
    case NOT_EQUAL: {
      result = (cmp_result != 0);
    } break;
    case LESS_THAN: {
      result = (cmp_result < 0);
    } break;
    case GREAT_EQUAL: {
      result = (cmp_result >= 0);
    } break;
    case GREAT_THAN: {
      result = (cmp_result > 0);
    } break;
    default: {
      LOG_WARN("unsupported comparison. %d", comp_);
      rc = RC::INTERNAL;
    } break;
  }

  return rc;
}

RC ComparisonExpr::try_get_value(Value &cell) const
{
  if (left_->type() == ExprType::VALUE && right_->type() == ExprType::VALUE) {
    ValueExpr   *left_value_expr  = static_cast<ValueExpr *>(left_.get());
    ValueExpr   *right_value_expr = static_cast<ValueExpr *>(right_.get());
    const Value &left_cell        = left_value_expr->get_value();
    const Value &right_cell       = right_value_expr->get_value();

    bool value = false;
    RC   rc    = compare_value(left_cell, right_cell, value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to compare tuple cells. rc=%s", strrc(rc));
    } else {
      cell.set_boolean(value);
    }
    return rc;
  }

  return RC::INVALID_ARGUMENT;
}

RC ComparisonExpr::get_value(const Tuple &tuple, Value &value)
{
  Value left_value;
  Value right_value;

  // 辅助函数：获取表达式值，处理子查询返回值
  auto get_expr_value = [&tuple](const std::unique_ptr<Expression> &expr, Value &value) -> RC {
    RC rc = expr->get_value(tuple, value);
    if (expr->type() == ExprType::SUBQUERY && rc == RC::RECORD_EOF) {
      value.set_null(true);
      return RC::SUCCESS;
    }
    return rc;
  };

  // 辅助函数：检查表达式是否为子查询并返回类型转换后的指针
  auto get_subquery_expr = [](const std::unique_ptr<Expression> &expr) -> SubQueryExpr * {
    return expr->type() == ExprType::SUBQUERY ? dynamic_cast<SubQueryExpr *>(expr.get()) : nullptr;
  };

  // 检查左侧和右侧是否为子查询表达式
  SubQueryExpr *left_subquery_expr  = get_subquery_expr(left_);
  SubQueryExpr *right_subquery_expr = get_subquery_expr(right_);

  // 处理 EXISTS 和 NOT EXISTS 操作
  if (comp_ == EXISTS_OP || comp_ == NOT_EXISTS_OP) {
    RC   rc     = right_->get_value(tuple, right_value);
    bool exists = (rc == RC::SUCCESS);
    value.set_boolean(comp_ == EXISTS_OP ? exists : !exists);
    // 调用 right_subquery_expr->close() 确保资源释放
    if (right_subquery_expr) {
      right_subquery_expr->close();
    }
    return exists ? RC::SUCCESS : RC::RECORD_EOF;
  }

  // 获取左值
  RC rc = get_expr_value(left_, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    // 调用 left_subquery_expr->close() 确保资源释放
    if (left_subquery_expr) {
      left_subquery_expr->close();
    }
    return rc;
  }

  // 检查子查询是否有多行结果
  if (left_subquery_expr && left_subquery_expr->has_more_row()) {
    left_subquery_expr->close();  // 关闭子查询
    return RC::INVALID_ARGUMENT;
  }

  // 处理 IN 和 NOT IN 操作
  if (comp_ == IN_OP || comp_ == NOT_IN_OP) {

    if (right_->type() == ExprType::EXPRLIST) {
      static_cast<ListExpr *>(right_.get())->reset();
    }

    if (left_value.is_null()) {
      value.set_boolean(false);
      if (right_subquery_expr) {
        right_subquery_expr->close();  // 关闭子查询
      }
      return RC::SUCCESS;
    }

    bool has_match = false;
    bool has_null  = false;

    while (RC::SUCCESS == (rc = right_->get_value(tuple, right_value))) {
      if (right_value.is_null()) {
        has_null = true;
      } else if (left_value.compare(right_value) == 0) {
        has_match = true;
      }
    }

    bool result = (comp_ == IN_OP) ? has_match : (!has_null && !has_match);
    value.set_boolean(result);
    // 调用 right_subquery_expr->close() 确保资源释放
    if (right_subquery_expr) {
      right_subquery_expr->close();
    }
    return (rc == RC::RECORD_EOF) ? RC::SUCCESS : rc;
  }

  // 获取右值
  rc = get_expr_value(right_, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    if (right_subquery_expr) {
      right_subquery_expr->close();
    }
    return rc;
  }

  // 检查右侧子查询是否有多行结果
  if (right_subquery_expr && right_subquery_expr->has_more_row()) {
    right_subquery_expr->close();
    return RC::INVALID_ARGUMENT;
  }

  // 比较左值和右值
  bool bool_value = false;
  rc              = compare_value(left_value, right_value, bool_value);
  if (rc == RC::SUCCESS) {
    value.set_boolean(bool_value);
  }

  // 调用 left_subquery_expr 和 right_subquery_expr 的 close 确保资源释放
  if (left_subquery_expr) {
    left_subquery_expr->close();
  }
  if (right_subquery_expr) {
    right_subquery_expr->close();
  }

  return rc;
}

RC ComparisonExpr::eval(Chunk &chunk, std::vector<uint8_t> &select)
{
  RC     rc = RC::SUCCESS;
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  if (left_column.attr_type() != right_column.attr_type()) {
    LOG_WARN("cannot compare columns with different types");
    return RC::INTERNAL;
  }
  if (left_column.attr_type() == AttrType::INTS) {
    rc = compare_column<int>(left_column, right_column, select);
  } else if (left_column.attr_type() == AttrType::FLOATS) {
    rc = compare_column<float>(left_column, right_column, select);
  } else {
    // TODO: support string compare
    LOG_WARN("unsupported data type %d", left_column.attr_type());
    return RC::INTERNAL;
  }
  return rc;
}

template <typename T>
RC ComparisonExpr::compare_column(const Column &left, const Column &right, std::vector<uint8_t> &result) const
{
  RC rc = RC::SUCCESS;

  bool left_const  = left.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    compare_result<T, true, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else if (left_const && !right_const) {
    compare_result<T, true, false>((T *)left.data(), (T *)right.data(), right.count(), result, comp_);
  } else if (!left_const && right_const) {
    compare_result<T, false, true>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  } else {
    compare_result<T, false, false>((T *)left.data(), (T *)right.data(), left.count(), result, comp_);
  }
  return rc;
}

////////////////////////////////////////////////////////////////////////////////
ConjunctionExpr::ConjunctionExpr(Type type, vector<unique_ptr<Expression>> &children)
    : conjunction_type_(type), children_(std::move(children))
{}
ConjunctionExpr::ConjunctionExpr(Type type, Expression *left, Expression *right) : conjunction_type_(type)
{
  children_.emplace_back(left);
  children_.emplace_back(right);
}
ConjunctionExpr::ConjunctionExpr(Type type, std::unique_ptr<Expression> children) : conjunction_type_(type)
{
  children_.push_back(std::move(children));
}

RC ConjunctionExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;
  if (children_.empty()) {
    value.set_boolean(true);
    return rc;
  }

  Value tmp_value;
  for (const unique_ptr<Expression> &expr : children_) {
    rc = expr->get_value(tuple, tmp_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value by child expression. rc=%s", strrc(rc));
      return rc;
    }
    bool bool_value = tmp_value.get_boolean();
    if ((conjunction_type_ == Type::AND && !bool_value) || (conjunction_type_ == Type::OR && bool_value)) {
      value.set_boolean(bool_value);
      return rc;
    }
  }

  bool default_value = (conjunction_type_ == Type::AND);
  value.set_boolean(default_value);
  return rc;
}

////////////////////////////////////////////////////////////////////////////////

ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, Expression *left, Expression *right)
    : arithmetic_type_(type), left_(left), right_(right)
{}
ArithmeticExpr::ArithmeticExpr(ArithmeticExpr::Type type, unique_ptr<Expression> left, unique_ptr<Expression> right)
    : arithmetic_type_(type), left_(std::move(left)), right_(std::move(right))
{}

bool ArithmeticExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (type() != other.type()) {
    return false;
  }
  auto &other_arith_expr = static_cast<const ArithmeticExpr &>(other);
  return arithmetic_type_ == other_arith_expr.arithmetic_type() && left_->equal(*other_arith_expr.left_) &&
         right_->equal(*other_arith_expr.right_);
}
AttrType ArithmeticExpr::value_type() const
{
  if (!right_) {
    return left_->value_type();
  }

  if (left_->value_type() == AttrType::INTS && right_->value_type() == AttrType::INTS &&
      arithmetic_type_ != Type::DIV) {
    return AttrType::INTS;
  }

  return AttrType::FLOATS;
}

RC ArithmeticExpr::calc_value(const Value &left_value, const Value &right_value, Value &value) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  value.set_type(target_type);

  switch (arithmetic_type_) {
    case Type::ADD: {
      Value::add(left_value, right_value, value);
    } break;

    case Type::SUB: {
      Value::subtract(left_value, right_value, value);
    } break;

    case Type::MUL: {
      Value::multiply(left_value, right_value, value);
    } break;

    case Type::DIV: {
      Value::divide(left_value, right_value, value);
    } break;

    case Type::NEGATIVE: {
      Value::negative(left_value, value);
    } break;

    default: {
      rc = RC::INTERNAL;
      LOG_WARN("unsupported arithmetic type. %d", arithmetic_type_);
    } break;
  }
  return rc;
}

template <bool LEFT_CONSTANT, bool RIGHT_CONSTANT>
RC ArithmeticExpr::execute_calc(
    const Column &left, const Column &right, Column &result, Type type, AttrType attr_type) const
{
  RC rc = RC::SUCCESS;
  switch (type) {
    case Type::ADD: {
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, AddOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, AddOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
    } break;
    case Type::SUB:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, SubtractOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, SubtractOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::MUL:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, MultiplyOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, MultiplyOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::DIV:
      if (attr_type == AttrType::INTS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, int, DivideOperator>(
            (int *)left.data(), (int *)right.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        binary_operator<LEFT_CONSTANT, RIGHT_CONSTANT, float, DivideOperator>(
            (float *)left.data(), (float *)right.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    case Type::NEGATIVE:
      if (attr_type == AttrType::INTS) {
        unary_operator<LEFT_CONSTANT, int, NegateOperator>((int *)left.data(), (int *)result.data(), result.capacity());
      } else if (attr_type == AttrType::FLOATS) {
        unary_operator<LEFT_CONSTANT, float, NegateOperator>(
            (float *)left.data(), (float *)result.data(), result.capacity());
      } else {
        rc = RC::UNIMPLEMENTED;
      }
      break;
    default: rc = RC::UNIMPLEMENTED; break;
  }
  if (rc == RC::SUCCESS) {
    result.set_count(result.capacity());
  }
  return rc;
}

RC ArithmeticExpr::get_value(const Tuple &tuple, Value &value)
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->get_value(tuple, left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_value(tuple, right_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_value(left_value, right_value, value);
}

RC ArithmeticExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
    return rc;
  }
  Column left_column;
  Column right_column;

  rc = left_->get_column(chunk, left_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of left expression. rc=%s", strrc(rc));
    return rc;
  }
  rc = right_->get_column(chunk, right_column);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get column of right expression. rc=%s", strrc(rc));
    return rc;
  }
  return calc_column(left_column, right_column, column);
}

RC ArithmeticExpr::calc_column(const Column &left_column, const Column &right_column, Column &column) const
{
  RC rc = RC::SUCCESS;

  const AttrType target_type = value_type();
  column.init(target_type, left_column.attr_len(), std::max(left_column.count(), right_column.count()));
  bool left_const  = left_column.column_type() == Column::Type::CONSTANT_COLUMN;
  bool right_const = right_column.column_type() == Column::Type::CONSTANT_COLUMN;
  if (left_const && right_const) {
    column.set_column_type(Column::Type::CONSTANT_COLUMN);
    rc = execute_calc<true, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (left_const && !right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<true, false>(left_column, right_column, column, arithmetic_type_, target_type);
  } else if (!left_const && right_const) {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, true>(left_column, right_column, column, arithmetic_type_, target_type);
  } else {
    column.set_column_type(Column::Type::NORMAL_COLUMN);
    rc = execute_calc<false, false>(left_column, right_column, column, arithmetic_type_, target_type);
  }
  return rc;
}

RC ArithmeticExpr::try_get_value(Value &value) const
{
  RC rc = RC::SUCCESS;

  Value left_value;
  Value right_value;

  rc = left_->try_get_value(left_value);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to get value of left expression. rc=%s", strrc(rc));
    return rc;
  }

  if (right_) {
    rc = right_->try_get_value(right_value);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to get value of right expression. rc=%s", strrc(rc));
      return rc;
    }
  }

  return calc_value(left_value, right_value, value);
}

////////////////////////////////////////////////////////////////////////////////

UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, Expression *child)
    : aggregate_name_(aggregate_name), child_(child)
{}
UnboundAggregateExpr::UnboundAggregateExpr(const char *aggregate_name, std::unique_ptr<Expression> child)
    : aggregate_name_(aggregate_name), child_(std::move(child))
{}

////////////////////////////////////////////////////////////////////////////////
AggregateExpr::AggregateExpr(Type type, Expression *child) : aggregate_type_(type), child_(child) {}

AggregateExpr::AggregateExpr(Type type, unique_ptr<Expression> child) : aggregate_type_(type), child_(std::move(child))
{}

RC AggregateExpr::get_column(Chunk &chunk, Column &column)
{
  RC rc = RC::SUCCESS;
  if (pos_ != -1) {
    column.reference(chunk.column(pos_));
  } else {
    rc = RC::INTERNAL;
  }
  return rc;
}

bool AggregateExpr::equal(const Expression &other) const
{
  if (this == &other) {
    return true;
  }
  if (other.type() != type()) {
    return false;
  }
  const AggregateExpr &other_aggr_expr = static_cast<const AggregateExpr &>(other);
  return aggregate_type_ == other_aggr_expr.aggregate_type() && child_->equal(*other_aggr_expr.child());
}

unique_ptr<Aggregator> AggregateExpr::create_aggregator() const
{
  unique_ptr<Aggregator> aggregator;
  switch (aggregate_type_) {
    case Type::SUM: {
      aggregator = make_unique<SumAggregator>();
      break;
    }
    case Type::COUNT: {
      aggregator = make_unique<CountAggregator>();
      break;
    }
    case Type::AVG: {
      aggregator = make_unique<AvgAggregator>();
      break;
    }
    case Type::MAX: {
      aggregator = make_unique<MaxAggregator>();
      break;
    }
    case Type::MIN: {
      aggregator = make_unique<MinAggregator>();
      break;
    }
    default: {
      ASSERT(false, "unsupported aggregate type");
      break;
    }
  }
  return aggregator;
}

RC AggregateExpr::get_value(const Tuple &tuple, Value &value) { return tuple.find_cell(TupleCellSpec(name()), value); }

RC AggregateExpr::type_from_string(const char *type_str, AggregateExpr::Type &type)
{
  RC rc = RC::SUCCESS;
  if (0 == strcasecmp(type_str, "count")) {
    type = Type::COUNT;
  } else if (0 == strcasecmp(type_str, "sum")) {
    type = Type::SUM;
  } else if (0 == strcasecmp(type_str, "avg")) {
    type = Type::AVG;
  } else if (0 == strcasecmp(type_str, "max")) {
    type = Type::MAX;
  } else if (0 == strcasecmp(type_str, "min")) {
    type = Type::MIN;
  } else {
    rc = RC::INVALID_ARGUMENT;
  }
  return rc;
}

SubQueryExpr::SubQueryExpr(SelectSqlNode &select_node) : sql_node_(select_node) {}

SubQueryExpr::~SubQueryExpr() = default;

RC SubQueryExpr::generate_select_stmt(Db *db, const std::unordered_map<std::string, Table *> &tables)
{
  // 仿照普通 select 的执行流程，tables 用来传递别名
  Stmt *stmt = nullptr;
  RC    rc   = SelectStmt::create(db, sql_node_, stmt);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to create subquery select statement. return %s", strrc(rc));
    return rc;
  }

  // 确保生成的 stmt 类型为 SELECT 类型
  if (stmt->type() != StmtType::SELECT) {
    LOG_WARN("subquery stmt type is not SELECT.");
    return RC::INVALID_ARGUMENT;
  }

  // 动态转换为 SelectStmt 类型，并进行子查询列数校验
  auto *select_stmt = dynamic_cast<SelectStmt *>(stmt);
  if (select_stmt == nullptr) {
    LOG_WARN("failed to cast subquery stmt to SelectStmt. ");
    return RC::INVALID_ARGUMENT;
  }

  // 子查询不能有超过一个列
  if (select_stmt->query_expressions_size() > 1) {
    LOG_WARN("too many columns in subquery expression.");
    return RC::TO_LONG_SUBQUERY_EXPR;
  }

  // 将 select_stmt_ 指针设置为 select_stmt，使用 std::unique_ptr 来管理
  select_stmt_ = std::unique_ptr<SelectStmt>(select_stmt);
  return RC::SUCCESS;
}

RC SubQueryExpr::generate_logical_oper()
{
  RC rc = LogicalPlanGenerator::create(select_stmt_.get(), logical_oper_);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to generate logical operator for subquery. return %s", strrc(rc));
    return rc;
  }
  return RC::SUCCESS;
}

RC SubQueryExpr::generate_physical_oper()
{
  RC rc = PhysicalPlanGenerator::create(*logical_oper_, physical_oper_);
  if (OB_FAIL(rc)) {
    LOG_WARN("failed to generate physical operator for subquery. return %s", strrc(rc));
    return rc;
  }
  return open(nullptr);
}
bool SubQueryExpr::one_row_ret() const { return res_query.size() <= 1; }

// 子算子树的 open 和 close 逻辑由外部控制
RC SubQueryExpr::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  rc    = physical_oper_->open(trx);
  if (OB_FAIL(rc)) {
    return rc;
  }

  Value sub_query_value;
  res_query.clear();
  while (RC::SUCCESS == physical_oper_->next()) {
    physical_oper_->current_tuple()->cell_at(0, sub_query_value);
    res_query.push_back(sub_query_value);
  }

  res_query_avaliable = true;
  visited_index       = 0;
  rc                  = physical_oper_->close();
  return rc;
}

RC SubQueryExpr::close()
{
  visited_index = 0;
  return RC::SUCCESS;
}

bool SubQueryExpr::has_more_row() const { return res_query.size() > 1; }

RC SubQueryExpr::get_value(const Tuple &tuple, Value &value)
{
  if (visited_index == res_query.size()) {
    return RC::RECORD_EOF;
  }
  value=res_query[visited_index++];
  return  RC::SUCCESS;
}

RC SubQueryExpr::try_get_value(Value &value) const { return RC::UNIMPLEMENTED; }

ExprType SubQueryExpr::type() const { return ExprType::SUBQUERY;
}

AttrType SubQueryExpr::value_type() const
{
  return AttrType::UNDEFINED;
}

std::unique_ptr<Expression> SubQueryExpr::deep_copy() const
{
  return {};
}

ListExpr::ListExpr(std::vector<Expression *> &&exprs)
{
  for (auto expr : exprs) {
    exprs_.emplace_back(std::unique_ptr<Expression>(expr));
  }
  exprs.clear();
}