/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                   *
 * @Description : create view executor source file             *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "sql/executor/create_view_executor.h"
#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/stmt/create_table_stmt.h"
#include "storage/db/db.h"
#include "sql/optimizer/logical_plan_generator.h"
#include "sql/operator/logical_operator.h"
#include "sql/operator/project_logical_operator.h"
#include "sql/optimizer/physical_plan_generator.h"
#include "storage/trx/trx.h"
#include "sql/stmt/create_view_stmt.h"

RC CreateViewExecutor::execute(SQLStageEvent *sql_event)
{
  RC       rc;
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::CREATE_VIEW,
      "create view executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  auto create_view_stmt = static_cast<CreateViewStmt *>(stmt);
  auto table_name       = create_view_stmt->table_name().c_str();
  auto select_stmt      = create_view_stmt->select_stmt();
  ASSERT(select_stmt != nullptr,
    "create view executor can not run this command: %d",
    static_cast<int>(stmt->type()));

  std::vector<AttrInfoSqlNode> attr_infos;
  for (auto &query_expr : select_stmt->query_expressions()) {
    AttrInfoSqlNode attr_info;
    if (auto field_expr = dynamic_cast<FieldExpr *>(query_expr.get())) {
      auto field_meta    = field_expr->field().meta();
      attr_info.type     = field_meta->type();
      attr_info.name     = field_meta->name();
      attr_info.length   = field_meta->len();
      attr_info.nullable = field_meta->nullable();
    } else {
      attr_info.type   = query_expr->value_type();
      attr_info.name   = query_expr->name();
      attr_info.length = query_expr->value_length();
    }
    attr_infos.emplace_back(std::move(attr_info));
  }

  unique_ptr<LogicalOperator> logical_oper = nullptr;
  LogicalPlanGenerator::create(select_stmt, logical_oper);
  if (!logical_oper) {
    return RC::INTERNAL;
  }

  unique_ptr<PhysicalOperator> physical_oper = nullptr;
  PhysicalPlanGenerator::create(*logical_oper, physical_oper);
  if (!physical_oper) {
    return RC::INTERNAL;
  }

  auto tables = select_stmt->tables();
  rc          = session->get_current_db()->create_table(
      table_name, attr_infos, tables, std::move(physical_oper), StorageFormat::ROW_FORMAT);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return rc;
}
