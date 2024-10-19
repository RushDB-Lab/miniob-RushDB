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
// Created by Wangyunlai on 2024/05/29.
//

#include <algorithm>

#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/expression_binder.h"
#include "sql/expr/expression_iterator.h"

using namespace std;
using namespace common;

BaseTable *BinderContext::find_table(const char *table_name) const
{
  auto iter = this->tables_->find(table_name);
  if (iter == tables_->end()) {
    return nullptr;
  }
  return iter->second;
}

////////////////////////////////////////////////////////////////////////////////
void ExpressionBinder::wildcard_fields(
    BaseTable *table, std::string table_alias, vector<unique_ptr<Expression>> &expressions, bool multi_tables)
{
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num();
  for (int i = table_meta.sys_field_num(); i < field_num; i++) {
    Field      field(table, table_meta.field(i));
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_table_alias(std::move(table_alias));
    // 这里设置了基类的 name 属性
    if (multi_tables) {
      // 多表查询带表名
      auto table_name = field_expr->table_name();
      auto field_name = field_expr->field_name();
      // 创建一个字符数组来存储合并后的字符串
      char result[256];
      // 使用 snprintf 合并字符串
      snprintf(result, sizeof(result), "%s.%s", table_name, field_name);
      field_expr->set_name(result);
    } else {
      // 单表查询不带表名
      field_expr->set_name(field.field_name());
    }
    expressions.emplace_back(field_expr);
  }
}

RC ExpressionBinder::bind_expression(unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  switch (expr->type()) {
    case ExprType::STAR: {
      return bind_star_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_FIELD: {
      return bind_unbound_field_expression(expr, bound_expressions);
    } break;

    case ExprType::UNBOUND_FUNCTION: {
      return bind_function_expression(expr, bound_expressions);
    } break;

    case ExprType::FIELD: {
      return bind_field_expression(expr, bound_expressions);
    } break;

    case ExprType::VALUE: {
      return bind_value_expression(expr, bound_expressions);
    } break;

    case ExprType::CAST: {
      return bind_cast_expression(expr, bound_expressions);
    } break;

    case ExprType::COMPARISON: {
      return bind_comparison_expression(expr, bound_expressions);
    } break;

    case ExprType::CONJUNCTION: {
      return bind_conjunction_expression(expr, bound_expressions);
    } break;

    case ExprType::ARITHMETIC: {
      return bind_arithmetic_expression(expr, bound_expressions);
    } break;

    case ExprType::AGGREGATION: {
      return bind_function_expression(expr, bound_expressions);
    } break;

    case ExprType::SUBQUERY: {
      return bind_subquery_expression(expr, bound_expressions);
    } break;

    case ExprType::EXPRLIST: {
      return bind_exprlist_expression(expr, bound_expressions);
    } break;
    default: {
      LOG_WARN("unknown expression type: %d", static_cast<int>(expr->type()));
      return RC::INTERNAL;
    }
  }
  return RC::INTERNAL;
}

RC ExpressionBinder::bind_star_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto star_expr = static_cast<StarExpr *>(expr.get());

  if (!is_blank(star_expr->name()) || !is_blank(star_expr->alias())) {
    return RC::INVALID_ALIAS;
  }

  vector<BaseTable *> tables_to_wildcard;

  const char *table_name = star_expr->table_name();
  if (!is_blank(table_name) && 0 != strcmp(table_name, "*")) {
    BaseTable *table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    tables_to_wildcard.push_back(table);
  } else {
    const vector<BaseTable *> &all_tables = context_.query_tables();
    tables_to_wildcard.insert(tables_to_wildcard.end(), all_tables.begin(), all_tables.end());
  }

  // select t2/table_alias_2.* from table_alias_1 t1, table_alias_2 t2 where t1.id < t2.id; 非自交可能指定也可能没
  // select t2.* from table_alias_1 t1, table_alias_1 t2 where t1.id < t2.id; 自交的话必然指定了别名
  if (tables_to_wildcard.size() == 1) {
    // 看看能不能找到对应的表名，能的话是第一种情况
    for (int i = 0; i < context_.query_tables().size(); ++i) {
      if (strcmp(context_.query_tables()[i]->name(), table_name) == 0) {
        table_name = context_.alias()[i].c_str();
      }
    }
    wildcard_fields(tables_to_wildcard[0], table_name, bound_expressions, multi_tables_);
  } else {
    for (int i = 0; i < tables_to_wildcard.size(); ++i) {
      wildcard_fields(tables_to_wildcard[i], context_.alias()[i], bound_expressions, multi_tables_);
    }
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_unbound_field_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto unbound_field_expr = static_cast<UnboundFieldExpr *>(expr.get());

  const char *table_name = unbound_field_expr->table_name();
  const char *field_name = unbound_field_expr->field_name();

  BaseTable *table = nullptr;
  if (is_blank(table_name)) {
    table = context_.default_table();
  } else {
    table = context_.find_table(table_name);
    if (nullptr == table) {
      LOG_INFO("no such table in from list: %s", table_name);
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }
  }

  std::string table_alias;
  if (context_.has_tables_alias()) {
    // 多表自交要投影某些列或者有谓词条件的，一定是通过别名进行查询
    if (strcmp(table->name(), table_name) != 0) {
      table_alias = table_name;
    }
  }

  if (0 == strcmp(field_name, "*")) {
    wildcard_fields(table, table_alias, bound_expressions, multi_tables_);
  } else {
    const FieldMeta *field_meta = table->table_meta().field(field_name);
    if (nullptr == field_meta) {
      LOG_INFO("no such field in table: %s.%s", table_name, field_name);
      return RC::SCHEMA_FIELD_MISSING;
    }

    Field      field(table, field_meta);
    FieldExpr *field_expr = new FieldExpr(field);
    field_expr->set_table_alias(table_alias);
    // 这里设置了基类的 name 属性
    if (!is_blank(unbound_field_expr->alias())) {
      field_expr->set_name(unbound_field_expr->alias());
    } else if (multi_tables_) {
      // 创建一个字符数组来存储合并后的字符串
      char result[256];
      // 使用 snprintf 合并字符串
      snprintf(result, sizeof(result), "%s.%s", table_name, field_name);
      field_expr->set_name(result);
    } else {
      // 单表查询不带表名
      field_expr->set_name(field_name);
    }
    bound_expressions.emplace_back(field_expr);
  }

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_field_expression(
    unique_ptr<Expression> &field_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  auto field = static_cast<FieldExpr *>(field_expr.get());
  // 这里设置了基类的 name 属性
  if (multi_tables_) {
    // 多表查询带表名
    auto table_name = field->table_name();
    auto field_name = field->field_name();
    // 创建一个字符数组来存储合并后的字符串
    char result[256];
    // 使用 snprintf 合并字符串
    snprintf(result, sizeof(result), "%s.%s", table_name, field_name);
    field_expr->set_name(result);
  }
  bound_expressions.emplace_back(std::move(field_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_value_expression(
    unique_ptr<Expression> &value_expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  bound_expressions.emplace_back(std::move(value_expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_cast_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto cast_expr = static_cast<CastExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &child_expr = cast_expr->child();

  RC rc = bind_expression(child_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid children number of cast expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }

  unique_ptr<Expression> &child = child_bound_expressions[0];
  if (child.get() == child_expr.get()) {
    return RC::SUCCESS;
  }

  child_expr.reset(child.release());
  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_comparison_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  RC rc = RC::SUCCESS;
  if (nullptr == expr) {
    return rc;
  }

  auto comparison_expr = dynamic_cast<ComparisonExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = comparison_expr->left();
  unique_ptr<Expression>        &right_expr = comparison_expr->right();

  if (nullptr != left_expr) {
    rc = bind_expression(left_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &left = child_bound_expressions[0];
    if (left.get() != left_expr.get()) {
      left_expr = std::move(left);
    }
  }
  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  if (child_bound_expressions.size() == 1) {
    unique_ptr<Expression> &right = child_bound_expressions[0];
    if (right.get() != right_expr.get()) {
      right_expr = std::move(right);
    }
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC ExpressionBinder::bind_conjunction_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto conjunction_expr = static_cast<ConjunctionExpr *>(expr.get());

  vector<unique_ptr<Expression>>  child_bound_expressions;
  vector<unique_ptr<Expression>> &children = conjunction_expr->children();

  for (unique_ptr<Expression> &child_expr : children) {
    child_bound_expressions.clear();

    RC rc = bind_expression(child_expr, child_bound_expressions);
    if (rc != RC::SUCCESS) {
      return rc;
    }

    if (child_bound_expressions.size() != 1) {
      LOG_WARN("invalid children number of conjunction expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }

    unique_ptr<Expression> &child = child_bound_expressions[0];
    if (child.get() != child_expr.get()) {
      child_expr = std::move(child);
    }
  }

  bound_expressions.emplace_back(std::move(expr));

  return RC::SUCCESS;
}

RC ExpressionBinder::bind_arithmetic_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto arithmetic_expr = static_cast<ArithmeticExpr *>(expr.get());

  vector<unique_ptr<Expression>> child_bound_expressions;
  unique_ptr<Expression>        &left_expr  = arithmetic_expr->left();
  unique_ptr<Expression>        &right_expr = arithmetic_expr->right();

  RC rc = bind_expression(left_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() != 1) {
    LOG_WARN("invalid left children number of comparison expression: %d", child_bound_expressions.size());
    return RC::INVALID_ARGUMENT;
  }
  if (!is_blank(expr->alias())) {
    expr->set_name(expr->alias());
  }
  unique_ptr<Expression> &left = child_bound_expressions[0];
  if (left.get() != left_expr.get()) {
    left_expr = std::move(left);
  }

  child_bound_expressions.clear();
  rc = bind_expression(right_expr, child_bound_expressions);
  if (OB_FAIL(rc)) {
    return rc;
  }

  if (child_bound_expressions.size() == 1) {
    unique_ptr<Expression> &right = child_bound_expressions[0];
    if (right.get() != right_expr.get()) {
      right_expr = std::move(right);
    }
  }

  bound_expressions.emplace_back(std::move(expr));
  return RC::SUCCESS;
}

RC check_aggregate_expression(AggregateFunctionExpr &expression)
{
  // 必须有一个子表达式
  Expression *child_expression = expression.child().get();
  if (nullptr == child_expression) {
    LOG_WARN("child expression of aggregate expression is null");
    return RC::INVALID_ARGUMENT;
  }

  // 校验数据类型与聚合类型是否匹配
  AggregateFunctionType aggregate_type   = expression.aggregate_type();
  AttrType              child_value_type = child_expression->value_type();
  switch (aggregate_type) {
    case AggregateFunctionType::SUM:
    case AggregateFunctionType::AVG: {
      // 仅支持数值类型
      if (child_value_type != AttrType::INTS && child_value_type != AttrType::FLOATS) {
        LOG_WARN("invalid child value type for aggregate expression: %d", static_cast<int>(child_value_type));
        return RC::INVALID_ARGUMENT;
      }
    } break;

    case AggregateFunctionType::COUNT:

    case AggregateFunctionType::MAX:
    case AggregateFunctionType::MIN: {
      // 任何类型都支持
    } break;
  }

  // 子表达式中不能再包含聚合表达式
  function<RC(std::unique_ptr<Expression> &)> check_aggregate_expr = [&](unique_ptr<Expression> &expr) -> RC {
    RC rc = RC::SUCCESS;
    if (expr->type() == ExprType::AGGREGATION) {
      LOG_WARN("aggregate expression cannot be nested");
      return RC::INVALID_ARGUMENT;
    }
    rc = ExpressionIterator::iterate_child_expr(*expr, check_aggregate_expr);
    return rc;
  };

  RC rc = ExpressionIterator::iterate_child_expr(expression, check_aggregate_expr);

  return rc;
}

RC ExpressionBinder::bind_function_expression(
    unique_ptr<Expression> &expr, vector<unique_ptr<Expression>> &bound_expressions)
{
  if (nullptr == expr) {
    return RC::SUCCESS;
  }

  auto                  unbound_function_expr = static_cast<UnboundFunctionExpr *>(expr.get());
  const char           *function_name         = unbound_function_expr->function_name();
  AggregateFunctionType aggregate_type;
  RC                    rc = AggregateFunctionExpr::type_from_string(function_name, aggregate_type);
  if (OB_SUCC(rc)) {
    if (unbound_function_expr->args().size() != 1) {
      return RC::INVALID_ARGUMENT;
    }
    unique_ptr<Expression>        &child_expr = unbound_function_expr->args().front();
    vector<unique_ptr<Expression>> child_bound_expressions;

    if (child_expr->type() == ExprType::STAR && aggregate_type == AggregateFunctionType::COUNT) {
      ValueExpr *value_expr = new ValueExpr(Value(1));
      child_expr.reset(value_expr);
      // count(*) 输出星号
      child_expr->set_name("*");
      unbound_function_expr->set_name(unbound_function_expr->to_string());
    } else {
      rc = bind_expression(child_expr, child_bound_expressions);
      if (OB_FAIL(rc)) {
        return rc;
      }

      if (child_bound_expressions.size() != 1) {
        LOG_WARN("invalid children number of aggregate expression: %d", child_bound_expressions.size());
        return RC::INVALID_ARGUMENT;
      }

      if (child_bound_expressions[0].get() != child_expr.get()) {
        child_expr.reset(child_bound_expressions[0].release());
      }
    }

    auto aggregate_expr = make_unique<AggregateFunctionExpr>(aggregate_type, std::move(child_expr));

    // set name 阶段
    aggregate_expr->set_name(unbound_function_expr->name());
    aggregate_expr->set_alias(unbound_function_expr->alias());
    rc = check_aggregate_expression(*aggregate_expr);
    if (OB_FAIL(rc)) {
      return rc;
    }
    bound_expressions.emplace_back(std::move(aggregate_expr));
    return RC::SUCCESS;
  }

  NormalFunctionType func_type;
  rc = NormalFunctionExpr::type_from_string(function_name, func_type);
  if (OB_SUCC(rc)) {
    vector<unique_ptr<Expression>> child_bound_expressions;
    for (auto &child_expr : unbound_function_expr->args()) {
      rc = bind_expression(child_expr, child_bound_expressions);
      if (OB_FAIL(rc)) {
        return rc;
      }
    }
    unbound_function_expr->set_args(std::move(child_bound_expressions));

    string name      = unbound_function_expr->name();
    auto   func_expr = make_unique<NormalFunctionExpr>(
        func_type, unbound_function_expr->function_name(), std::move(unbound_function_expr->args()));
    func_expr->set_name(name);
    func_expr->set_alias(unbound_function_expr->alias());
    bound_expressions.emplace_back(std::move(func_expr));
    return RC::SUCCESS;
  }

  return RC::UNKNOWN_FUNCTION;
}

RC ExpressionBinder::bind_subquery_expression(
    std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions)
{
  RC   rc            = RC::SUCCESS;
  auto subquery_expr = dynamic_cast<SubQueryExpr *>(expr.get());

  rc = subquery_expr->generate_select_stmt(context_.get_db(), context_.table_map());
  if (OB_FAIL(rc)) {
    return rc;
  }
  rc = subquery_expr->generate_logical_oper();
  if (OB_FAIL(rc)) {
    return rc;
  }
  rc = subquery_expr->generate_physical_oper();

  bound_expressions.emplace_back(std::move(expr));
  return rc;
}

RC ExpressionBinder::bind_exprlist_expression(
    std::unique_ptr<Expression> &expr, std::vector<std::unique_ptr<Expression>> &bound_expressions)
{
  RC                             rc        = RC::SUCCESS;
  auto                           list_expr = dynamic_cast<ListExpr *>(expr.get());
  vector<unique_ptr<Expression>> child_bound_expressions;
  for (auto &child_expr : list_expr->get_list()) {
    if (child_expr->type() != ExprType::VALUE) {
      LOG_WARN("invalid children type of LIST expression: %d", child_bound_expressions.size());
      return RC::INVALID_ARGUMENT;
    }
  }

  bound_expressions.emplace_back(std::move(expr));
  return rc;
}
