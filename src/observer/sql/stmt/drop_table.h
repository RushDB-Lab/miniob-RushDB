#include <string>
#include <vector>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"

class Db;

class DropTableStmt : public Stmt
{
public:
  DropTableStmt(const std::string &table_name) : table_name_(table_name){};
  virtual ~DropTableStmt() = default;
  std::string table_name(){return table_name_;}

  StmtType type() const override { return StmtType::DROP_TABLE; }

  static RC drop(Db *db, DropTableSqlNode &drop_table, Stmt *&stmt);

private:
  std::string table_name_;
};