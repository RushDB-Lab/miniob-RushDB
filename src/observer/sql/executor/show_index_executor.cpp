/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/29                                    *
 * @Description : ShowIndexExecutor source file                *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "sql/executor/show_index_executor.h"
#include "sql/stmt/stmt.h"
#include "event/session_event.h"
#include "common/log/log.h"
#include "event/sql_event.h"
#include "session/session.h"
#include "sql/operator/string_list_physical_operator.h"
#include "sql/stmt/desc_table_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include "sql/stmt/show_index_stmt.h"

RC ShowIndexExecutor::execute(SQLStageEvent *sql_event)
{
  RC            rc            = RC::SUCCESS;
  Stmt         *stmt          = sql_event->stmt();
  SessionEvent *session_event = sql_event->session_event();
  Session      *session       = session_event->session();
  ASSERT(stmt->type() == StmtType::SHOW_INDEX,
      "show index executor can not run this command: %d",
      static_cast<int>(stmt->type()));

  ShowIndexStmt *show_index_stmt = static_cast<ShowIndexStmt *>(stmt);
  SqlResult     *sql_result      = session_event->sql_result();
  const char    *table_name      = show_index_stmt->table_name().c_str();

  Db        *db    = session->get_current_db();
  BaseTable *table = db->find_table(table_name);
  if (table != nullptr) {
    TupleSchema tuple_schema;
    tuple_schema.append_cell(TupleCellSpec("", "Table", "Table"));
    tuple_schema.append_cell(TupleCellSpec("", "Non_unique", "Non_unique"));
    tuple_schema.append_cell(TupleCellSpec("", "Key_name", "Key_name"));
    tuple_schema.append_cell(TupleCellSpec("", "Seq_in_index", "Seq_in_index"));
    tuple_schema.append_cell(TupleCellSpec("", "Column_name", "Column_name"));
    sql_result->set_tuple_schema(tuple_schema);

    auto             oper       = new StringListPhysicalOperator;
    const TableMeta &table_meta = table->table_meta();
    for (int i = 0; i < table_meta.index_num(); i++) {
      auto index = table_meta.index(i);
      for (size_t j = 0; j < index->fields().size(); j++) {
        auto           unique     = index->unique() ? "0" : "1";
        auto           name       = index->name();
        auto           id         = std::to_string(j + 1);
        auto           field_name = index->fields()[j].name();
        vector<string> list       = {table_name, unique, name, id, field_name};
        oper->append(list);
      }
    }

    sql_result->set_operator(unique_ptr<PhysicalOperator>(oper));
  } else {
    sql_result->set_return_code(RC::SCHEMA_TABLE_NOT_EXIST);
    sql_result->set_state_string("Table not exists");
  }
  return rc;
}
