#include "sql/executor/drop_table_executor.h"

#include "session/session.h"
#include "common/log/log.h"
#include "sql/stmt/drop_table.h"
#include "storage/table/table.h"
#include "sql/stmt/create_table_stmt.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "storage/db/db.h"


RC DropTableExecutor::execute(SQLStageEvent *sql_event){
    SqlResult *sql_result = sql_event->session_event()->sql_result();
    SessionEvent *session_event = sql_event->session_event();
    Stmt *stmt = sql_event->stmt();
    DropTableStmt *drop_table_stmt = static_cast<DropTableStmt *>(stmt);

    Db *db = session_event->session()->get_current_db();

    RC rc=db->drop_table(drop_table_stmt->table_name());
    return rc;

}