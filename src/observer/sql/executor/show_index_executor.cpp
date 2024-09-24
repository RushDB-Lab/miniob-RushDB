#include "sql/executor/show_index_executor.h"
#include "event/session_event.h"
#include "session/session.h"
#include "sql/executor/sql_result.h"
#include "sql/operator/string_list_physical_operator.h"
#include "sql/stmt/update_stmt.h"
#include "storage/db/db.h"
#include <string>

RC ShowIndexExecutor::execute(SQLStageEvent *sql_event)
{
  // 拿到基础数据
  // RC            rc            = RC::SUCCESS;
  // SqlResult    *sql_result    = sql_event->session_event()->sql_result();
  // SessionEvent *session_event = sql_event->session_event();
  // Stmt         *stmt          = sql_event->stmt();
  // UpdateStmt   *updata_stmt   = static_cast<UpdateStmt *>(stmt);
  // Db           *db            = session_event->session()->get_current_db();
  // Table        *table         = updata_stmt->table();

  SqlResult    *sql_result    = sql_event->session_event()->sql_result();
  SessionEvent *session_event = sql_event->session_event();

  Db *db = session_event->session()->get_current_db();

  std::vector<std::string> all_tables;
  db->all_tables(all_tables);

  TupleSchema tuple_schema;
  tuple_schema.append_cell(TupleCellSpec("", "Tables_in_SYS", "Tables_in_SYS"));
  sql_result->set_tuple_schema(tuple_schema);

  auto oper = new StringListPhysicalOperator;
  for (const std::string &s : all_tables) {
    oper->append(s);
  }

  sql_result->set_operator(std::unique_ptr<PhysicalOperator>(oper));
  return RC::SUCCESS;

  return RC::SUCCESS;
}
