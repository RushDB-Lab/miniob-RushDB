/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/18                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "sql/operator/logical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/operator/limit_logical_operator.h"
#include "sql/operator/order_by_logical_operator.h"
#include "sql/operator/table_get_logical_operator.h"
#include "sql/optimizer/vector_index_scan_rewrite.h"

RC VectorIndexScanRewrite::rewrite(std::unique_ptr<LogicalOperator> &oper, bool &change_made)
{
  auto &child_opers = oper->children();
  if (child_opers.size() != 1) {
    return RC::SUCCESS;
  }

  auto &child_oper = child_opers.front();
  if (child_oper->type() != LogicalOperatorType::LIMIT && child_oper->type() != LogicalOperatorType::ORDER_BY) {
    return RC::SUCCESS;
  }

  // 有 limit 且 orderby 是向量 重写为向量索引
  if (child_oper->type() == LogicalOperatorType::LIMIT) {
    auto &orderby_opers = child_oper->children();
    if (orderby_opers.size() != 1) {
      return RC::SUCCESS;
    }

    auto &orderby_oper = orderby_opers[0];
    if (orderby_oper->type() != LogicalOperatorType::ORDER_BY) {
      return RC::SUCCESS;
    }

    auto  act_orderby_oper = dynamic_cast<OrderByLogicalOperator *>(orderby_oper.get());
    auto &orderby_node     = act_orderby_oper->order_by();
    if (orderby_node.size() != 1 || !orderby_node[0].is_asc) {
      return RC::SUCCESS;
    }

    auto &expr = orderby_node[0].expr;
    if (expr->type() == ExprType::NORMAL_FUNCTION) {
      auto func_expr = dynamic_cast<NormalFunctionExpr *>(expr.get());
      if (!func_expr->is_vector_distance_func()) {
        return RC::SUCCESS;
      }

      auto &table_scan_oper = orderby_oper->children()[0];
      if (table_scan_oper->type() != LogicalOperatorType::TABLE_GET) {
        return RC::SUCCESS;
      }

      auto       table_get_oper = dynamic_cast<TableGetLogicalOperator *>(table_scan_oper.get());
      BaseTable *base_table     = table_get_oper->table();
      if (base_table->type() != TableType::Table) {
        return RC::SUCCESS;
      }

      auto table = dynamic_cast<Table *>(base_table);

      // 找到向量列和常量向量，目前只支持向量列与常量向量
      FieldExpr *field_expr;
      RowTuple   tuple;
      Value      value;

      if (func_expr->args()[0]->type() == ExprType::FIELD) {
        field_expr = dynamic_cast<FieldExpr *>(func_expr->args()[0].get());
        func_expr->args()[1]->get_value(tuple, value);
      } else {
        field_expr = dynamic_cast<FieldExpr *>(func_expr->args()[1].get());
        func_expr->args()[0]->get_value(tuple, value);
      }

      // 检查该列上是否建立了索引
      auto &field = field_expr->field();

      if (strcmp(table->name(), field.table_name()) != 0) {
        return RC::SUCCESS;
      }

      Index *index = table->find_vector_index(func_expr->function_type(), field.field_name());
      if (index == nullptr) {
        return RC::SUCCESS;
      }

      auto limit_oper = dynamic_cast<LimitLogicalOperator *>(child_oper.get());

      // 设置向量索引必要的参数
      table_get_oper->set_index(index);
      table_get_oper->set_base_vector(value.get_vector());
      table_get_oper->set_limit(limit_oper->limit());

      // 直接变成 proj table_get
      oper->children()[0] = std::move(table_scan_oper);
      change_made         = true;
    }
  }

  return RC::SUCCESS;
}
