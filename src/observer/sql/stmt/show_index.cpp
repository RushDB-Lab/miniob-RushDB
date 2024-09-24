#include "common/log/log.h"
#include "common/rc.h"
#include "src/observer/sql/stmt/show_index.h"
RC ShowIndexStmt ::create(Db *db, const ShowIndexSqlNode &showindex_sql, Stmt *&stmt)
{
  RC          rc         = RC::SUCCESS;
  const char *table_name = showindex_sql.relation_name.c_str();
  if (nullptr == db || nullptr == table_name) {
    LOG_WARN("invalid argument. db=%p, table_name=%p", db, table_name);
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  stmt = new ShowIndexStmt(table, table->indexes());
  return rc;
}