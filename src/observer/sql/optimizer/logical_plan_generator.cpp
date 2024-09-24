/* Copyright (c) 2023 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2023/08/16.
//

#include "sql/optimizer/logical_plan_generator.h"

#include "sql/operator/logical_operator.h"
#include "sql/operator/calc_logical_operator.h"
#include "sql/operator/orderby_operator/order_by_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/predicate_logical_operator.h"
#include "sql/operator/show_index_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/operator/insert_logical_operator.h"
#include "sql/operator/delete_logical_operator.h"
#include "sql/operator/join_logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/operator/explain_logical_operator.h"
#include "sql/operator/agg_func_logical_operator.h"

#include "sql/operator/update_logical_operator.h"
#include "sql/stmt/show_index.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/filter_stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/update_stmt.h"
#include <cstddef>

using namespace std;

RC LogicalPlanGenerator::create(Stmt *stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  RC rc = RC::SUCCESS;
  switch (stmt->type()) {
    case StmtType::CALC: {
      CalcStmt *calc_stmt = static_cast<CalcStmt *>(stmt);
      rc                  = create_plan(calc_stmt, logical_operator);
    } break;

    case StmtType::SELECT: {
      SelectStmt *select_stmt = static_cast<SelectStmt *>(stmt);
      rc                      = create_plan(select_stmt, logical_operator);
    } break;

    case StmtType::INSERT: {
      InsertStmt *insert_stmt = static_cast<InsertStmt *>(stmt);
      rc                      = create_plan(insert_stmt, logical_operator);
    } break;

    case StmtType::DELETE: {
      DeleteStmt *delete_stmt = static_cast<DeleteStmt *>(stmt);
      rc                      = create_plan(delete_stmt, logical_operator);
    } break;

    case StmtType::EXPLAIN: {
      ExplainStmt *explain_stmt = static_cast<ExplainStmt *>(stmt);
      rc                        = create_plan(explain_stmt, logical_operator);
    } break;
    case StmtType::UPDATE: {
      UpdateStmt *update_stmt = static_cast<UpdateStmt *>(stmt);
      rc                      = create_plan(update_stmt, logical_operator);
    } break;
    case StmtType::SHOW_INDEX: {
      ShowIndexStmt *show_index_stmt = static_cast<ShowIndexStmt *>(stmt);
      rc                             = create_plan(show_index_stmt, logical_operator);
      // rc = RC::UNIMPLENMENT;
    } break;
    default: {
      rc = RC::UNIMPLENMENT;
    }
  }
  return rc;
}

RC LogicalPlanGenerator::create_plan(CalcStmt *calc_stmt, std::unique_ptr<LogicalOperator> &logical_operator)
{
  logical_operator.reset(new CalcLogicalOperator(std::move(calc_stmt->expressions())));
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(SelectStmt *select_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  const std::vector<Table *> &tables     = select_stmt->tables();
  const std::vector<Field>   &all_fields = select_stmt->query_fields();

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(select_stmt->filter_stmt(), predicate_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create predicate logical plan. rc=%s", strrc(rc));
    return rc;
  }

  // 先将每个table分类
  for (Table *table : tables) {
    std::vector<Field> fields;
    for (const Field &field : all_fields) {
      if (0 == strcmp(field.table_name(), table->name())) {
        fields.push_back(field);
      }
    }
    // 判断是否是聚合函数，并获取它的遍历表执行计划
    unique_ptr<LogicalOperator> table_get_oper;
    if (select_stmt->agg_func().empty()) {
      table_get_oper.reset(new TableGetLogicalOperator(table, fields, true /*readonly*/));
    } else {
      predicate_oper = nullptr;
      auto temp      = new AggFuncLogicalOperator(table, fields, select_stmt->agg_func(), true);
      temp->creat_predicates_(select_stmt->filter_stmt());
      table_get_oper.reset(temp);
    }

    if (table_oper == nullptr) {
      table_oper = std::move(table_get_oper);
    } else {
      JoinLogicalOperator *join_oper = new JoinLogicalOperator;
      // 先放第一个的执行计划
      join_oper->add_child(std::move(table_oper));
      // 再放刚刚的执行计划
      join_oper->add_child(std::move(table_get_oper));
      table_oper = unique_ptr<LogicalOperator>(join_oper);
    }
  }

  // 封装成project执行计划
  unique_ptr<LogicalOperator> project_oper(new ProjectLogicalOperator(all_fields, tables));

  // order by的执行计划
  unique_ptr<LogicalOperator> orderby_oper(new OrderByLogicalOperator(select_stmt->get_OrderBy()));
  if (select_stmt->get_OrderBy().size() != 0) {
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      project_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        project_oper->add_child(std::move(table_oper));
      }
    }
    orderby_oper->add_child(std::move(project_oper));
    logical_operator.swap(orderby_oper);
  } else {
    if (predicate_oper) {
      if (table_oper) {
        predicate_oper->add_child(std::move(table_oper));
      }
      project_oper->add_child(std::move(predicate_oper));
    } else {
      if (table_oper) {
        project_oper->add_child(std::move(table_oper));
      }
    }
    logical_operator.swap(project_oper);
  }

  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(ShowIndexStmt *show_inedx_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  unique_ptr<LogicalOperator> table_oper(nullptr);

  Table                     *table    = show_inedx_stmt->tables();
  const std::vector<Index *> indexes_ = show_inedx_stmt->indexs();

  unique_ptr<LogicalOperator> project_oper(new ShowIndexLogicalOperator(indexes_, table));
  logical_operator.swap(project_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(FilterStmt *filter_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  std::vector<unique_ptr<Expression>> cmp_exprs;
  const std::vector<FilterUnit *>    &filter_units = filter_stmt->filter_units();
  for (const FilterUnit *filter_unit : filter_units) {
    const FilterObj &filter_obj_left  = filter_unit->left();
    const FilterObj &filter_obj_right = filter_unit->right();

    unique_ptr<Expression> left(filter_obj_left.is_attr
                                    ? static_cast<Expression *>(new FieldExpr(filter_obj_left.field))
                                    : static_cast<Expression *>(new ValueExpr(filter_obj_left.value)));

    unique_ptr<Expression> right(filter_obj_right.is_attr
                                     ? static_cast<Expression *>(new FieldExpr(filter_obj_right.field))
                                     : static_cast<Expression *>(new ValueExpr(filter_obj_right.value)));

    ComparisonExpr *cmp_expr = new ComparisonExpr(filter_unit->comp(), std::move(left), std::move(right));
    cmp_exprs.emplace_back(cmp_expr);
  }

  unique_ptr<PredicateLogicalOperator> predicate_oper;
  if (!cmp_exprs.empty()) {
    unique_ptr<ConjunctionExpr> conjunction_expr(new ConjunctionExpr(ConjunctionExpr::Type::AND, cmp_exprs));
    predicate_oper = unique_ptr<PredicateLogicalOperator>(new PredicateLogicalOperator(std::move(conjunction_expr)));
  }
  // 建立select子查询逻辑计划
  std::vector<SelectStmt *> child_select_stmt_ = filter_stmt->child_select_stmt();
  if (child_select_stmt_.size() == 0) {
    logical_operator = std::move(predicate_oper);
    return RC::SUCCESS;
  }
  std::vector<std::unique_ptr<LogicalOperator>> child_select_logical_operator(child_select_stmt_.size());
  for (int i = child_select_stmt_.size() - 1; i >= 0; i--) {
    RC rc = create_plan(child_select_stmt_[i], child_select_logical_operator[i]);
    if (rc != RC::SUCCESS) {
      return rc;
    }
  }
  predicate_oper->set_logical_child_operator(std::move(child_select_logical_operator));
  logical_operator = std::move(predicate_oper);
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(InsertStmt *insert_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table                *table  = insert_stmt->table();
  vector<vector<Value>> values = insert_stmt->values();

  InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  logical_operator.reset(insert_operator);  // 转移指向的所有权
  return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(UpdateStmt *update_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  // 获取表明的更新的数据
  Table *table = update_stmt->table();

  vector<Value>            values;
  std::vector<std::string> att_names;
  for (auto temp : update_stmt->Updatenodes()) {
    values.push_back(temp.value);
    att_names.push_back(temp.attribute_name);
  }
  FilterStmt        *filter_stmt = update_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  // 根据过滤条件更新filter
  unique_ptr<LogicalOperator> predicate_oper;  // predicate--谓语句子成分
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> update_oper(new UpdateLogicalOperator(table, att_names, values));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    update_oper->add_child(std::move(predicate_oper));
  } else {
    update_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(update_oper);
  return rc;

  // InsertLogicalOperator *insert_operator = new InsertLogicalOperator(table, values);
  // logical_operator.reset(insert_operator);
  // return RC::SUCCESS;
}

RC LogicalPlanGenerator::create_plan(DeleteStmt *delete_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Table             *table       = delete_stmt->table();
  FilterStmt        *filter_stmt = delete_stmt->filter_stmt();
  std::vector<Field> fields;
  for (int i = table->table_meta().sys_field_num(); i < table->table_meta().field_num(); i++) {
    const FieldMeta *field_meta = table->table_meta().field(i);
    fields.push_back(Field(table, field_meta));
  }
  unique_ptr<LogicalOperator> table_get_oper(new TableGetLogicalOperator(table, fields, false /*readonly*/));

  unique_ptr<LogicalOperator> predicate_oper;
  RC                          rc = create_plan(filter_stmt, predicate_oper);
  if (rc != RC::SUCCESS) {
    return rc;
  }

  unique_ptr<LogicalOperator> delete_oper(new DeleteLogicalOperator(table));

  if (predicate_oper) {
    predicate_oper->add_child(std::move(table_get_oper));
    delete_oper->add_child(std::move(predicate_oper));
  } else {
    delete_oper->add_child(std::move(table_get_oper));
  }

  logical_operator = std::move(delete_oper);
  return rc;
}

RC LogicalPlanGenerator::create_plan(ExplainStmt *explain_stmt, unique_ptr<LogicalOperator> &logical_operator)
{
  Stmt                       *child_stmt = explain_stmt->child();
  unique_ptr<LogicalOperator> child_oper;
  RC                          rc = create(child_stmt, child_oper);
  if (rc != RC::SUCCESS) {
    LOG_WARN("failed to create explain's child operator. rc=%s", strrc(rc));
    return rc;
  }

  logical_operator = unique_ptr<LogicalOperator>(new ExplainLogicalOperator);
  logical_operator->add_child(std::move(child_oper));
  return rc;
}
