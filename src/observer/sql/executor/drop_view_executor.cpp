/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "common/log/log.h"
#include "event/session_event.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "storage/db/db.h"
#include "sql/stmt/drop_view_stmt.h"
#include "sql/executor/drop_view_executor.h"

RC DropViewExecutor::execute(SQLStageEvent *sql_event)
{
  Stmt    *stmt    = sql_event->stmt();
  Session *session = sql_event->session_event()->session();
  ASSERT(stmt->type() == StmtType::DROP_VIEW,
      "drop view executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  auto *drop_view_stmt = dynamic_cast<DropViewStmt *>(stmt);

  const char *table_name = drop_view_stmt->table_name().c_str();
  RC          rc         = session->get_current_db()->drop_table(table_name);

  return rc;
}
