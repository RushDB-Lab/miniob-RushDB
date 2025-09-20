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
#include "storage/trx/trx.h"
#include "sql/stmt/create_view_stmt.h"

// 提取 AS 后的 SQL 语句
std::string extract_select_sql(const std::string &createViewSql)
{
  std::string lowerSql = createViewSql;
  common::str_to_lower(lowerSql);

  std::string asToken = " as ";

  auto pos = lowerSql.find(asToken);
  if (pos == std::string::npos) {
    return "";
  }

  // 计算实际 SQL 句子的起始位置
  auto actualPos = pos + asToken.length();
  return createViewSql.substr(actualPos);
}

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

  auto select_sql = extract_select_sql(sql_event->sql());
  if (select_sql.empty()) {
    return RC::SQL_SYNTAX;
  }

  rc = session->get_current_db()->create_table(table_name,
      std::move(create_view_stmt->attr_names()),
      std::move(select_sql),
      select_stmt,
      StorageFormat::ROW_FORMAT);
  if (OB_FAIL(rc)) {
    return rc;
  }

  return rc;
}
