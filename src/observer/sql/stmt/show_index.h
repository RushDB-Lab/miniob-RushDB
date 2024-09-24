#pragma once

#include <string>
#include <vector>

#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "storage/table/table.h"

class Db;

/**
 * @brief 展示一个表索引的语句
 * @ingroup Statement
 * @details 虽然解析成了stmt，但是与原始的SQL解析后的数据也差不多
 */
class ShowIndexStmt : public Stmt
{
public:
  ShowIndexStmt(Table *table_, std::vector<Index *> indexs) : table(table_), indexes_(indexs) {}
  virtual ~ShowIndexStmt() = default;

  StmtType type() const override { return StmtType::SHOW_INDEX; }

  static RC create(Db *db, const ShowIndexSqlNode &showindex_sql, Stmt *&stmt);

  Table               *tables() { return table; }
  std::vector<Index *> indexs() { return indexes_; }

private:
  Table               *table = nullptr;
  std::vector<Index *> indexes_;
};