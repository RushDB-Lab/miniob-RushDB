#pragma once

#include <string>
#include <vector>
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse.h"

class UpdateStmt;

/**
 * @brief 更新物理算子
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator() = default;
  UpdatePhysicalOperator(Table *table, std::vector<std::string> names, std::vector<Value> &&values);

  virtual ~UpdatePhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC   open(Trx *trx) override;
  RC   next() override;
  RC   close() override;
  auto name() { return att_names; }

  Tuple *current_tuple() override { return nullptr; }

private:
  Table                   *table_ = nullptr;
  Trx                     *trx_   = nullptr;
  std::vector<std::string> att_names;
  std::vector<Value>       values_;
};

/*DELETE FROM multi_index3 WHERE id = 4 and col1 = 2;
DELETE FROM multi_index3 WHERE id = 9 and col1 = 1;
DELETE FROM multi_index3 WHERE id = 3 and col1 = 2;
DELETE FROM multi_index3 WHERE id = 7 and col1 = 1;

SELECT * FROM multi_index3;

CREATE TABLE multi_index3(id int, col1 int, col2 float, col3 char(10), col4 date, col5 int, col6 int);
CREATE INDEX i_3_i1 ON multi_index3(id,col1);
insert into multi_index3 VALUES (2, 1, 37.61, 'XZE2HC', '2006-03-04', 9, 81);
insert into multi_index3 VALUES (9, 1, 33.55, 'EMK05550Q', '2008-06-26', 2, 15);
insert into multi_index3 VALUES (7, 1, 13.60, 'LDF', '2001-11-11', 6, 45);
...
-- influence of inserting2
CREATE INDEX i_3_14 ON multi_index3(col1,col4);
insert into multi_index3 VALUES (8, 1, 32.73, 'S9NAVMHW', '2002-03-18', 4, 49);
insert into multi_index3 VALUES (8, 2, 29.24, 'O', '2001-03-13', 3, 93);
insert into multi_index3 VALUES (2, 2, 23.51, 'OG6MHPKZ', '2005-03-14', 5, 78);
insert into multi_index3 VALUES (2, 2, 24.54, 'SMN02IIIG', '2019-10-27', 4, 47);
...
-- influence of deleting
DELETE FROM multi_index3 WHERE id = 7;
DELETE FROM multi_index3 WHERE id = 6;
-- influence of deleting
DELETE FROM multi_index3 WHERE col3 = 'L';*/