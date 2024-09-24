#include "sql/stmt/drop_table.h"

RC DropTableStmt::drop(Db *db, DropTableSqlNode &drop_table, Stmt *&stmt)
{
  stmt = new DropTableStmt(drop_table.relation_name);
  // sql_debug("create table statement: table name %s", drop_table.relation_name.c_str());
  return RC::SUCCESS;
}