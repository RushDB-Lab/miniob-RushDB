/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "common/log/log.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/insert_stmt.h"
#include "sql/stmt/delete_stmt.h"
#include "sql/stmt/select_stmt.h"
#include "sql/stmt/explain_stmt.h"
#include "sql/stmt/create_index_stmt.h"
#include "sql/stmt/create_table_stmt.h"
#include "sql/stmt/desc_table_stmt.h"
#include "sql/stmt/help_stmt.h"
#include "sql/stmt/show_tables_stmt.h"
#include "sql/stmt/trx_begin_stmt.h"
#include "sql/stmt/trx_end_stmt.h"
#include "sql/stmt/exit_stmt.h"
#include "sql/stmt/set_variable_stmt.h"
#include "sql/stmt/load_data_stmt.h"
#include "sql/stmt/calc_stmt.h"
#include "sql/stmt/drop_table.h"
#include "sql/stmt/update_stmt.h"
#include "src/observer/sql/stmt/show_index.h"

RC Stmt::create_stmt(Db *db, ParsedSqlNode &sql_node, Stmt *&stmt)
{
  stmt = nullptr;

  switch (sql_node.flag) {
    case SCF_INSERT: {
      return InsertStmt::create(db, sql_node.insertion, stmt);
    }
    case SCF_DELETE: {
      return DeleteStmt::create(db, sql_node.deletion, stmt);
    }
    case SCF_SELECT: {
      return SelectStmt::create(db, sql_node.selection, stmt);
    }

    case SCF_EXPLAIN: {
      return ExplainStmt::create(db, sql_node.explain, stmt);
    }

    case SCF_CREATE_INDEX: {
      return CreateIndexStmt::create(db, sql_node.create_index, stmt);
    }

    case SCF_CREATE_TABLE: {
      return CreateTableStmt::create(db, sql_node.create_table, stmt);
    }

    case SCF_DESC_TABLE: {
      return DescTableStmt::create(db, sql_node.desc_table, stmt);
    }

    case SCF_HELP: {
      return HelpStmt::create(stmt);
    }

    case SCF_SHOW_TABLES: {
      return ShowTablesStmt::create(db, stmt);
    }

    case SCF_BEGIN: {
      return TrxBeginStmt::create(stmt);
    }

    case SCF_COMMIT:
    case SCF_ROLLBACK: {
      return TrxEndStmt::create(sql_node.flag, stmt);
    }

    case SCF_EXIT: {
      return ExitStmt::create(stmt);
    }

    case SCF_SET_VARIABLE: {
      return SetVariableStmt::create(sql_node.set_variable, stmt);
    }

    case SCF_LOAD_DATA: {
      return LoadDataStmt::create(db, sql_node.load_data, stmt);
    }

    case SCF_CALC: {
      return CalcStmt::create(sql_node.calc, stmt);
    }

    case SCF_DROP_TABLE: {
      return DropTableStmt::drop(db, sql_node.drop_table, stmt);
    }

    case SCF_UPDATE: {
      return UpdateStmt::create(db, sql_node.update, stmt);
    }

    case SCF_SHOW_INDEX: {
      return ShowIndexStmt::create(db, sql_node.show_index,stmt);
    }

    default: {
      LOG_INFO("Command::type %d doesn't need to create statement.", sql_node.flag);
    } break;
  }
  return RC::UNIMPLENMENT;
}
/*
Select * from join_table_1 inner join join_table_2 on join_table_1.id=join_table_2.id and join_table_2.age>15 inner join join_table_3 on join_table_1.id=join_table_2.id and join_table_3.level>=5;
- 1 | a | 1 | 18 | 1 | 5
- 1 | a | 1 | 18 | 3 | 6
+ 1 | a | 1 | 5 | 1 | 18
+ 1 | a | 3 | 6 | 1 | 18
-- below are some requests executed before(partial) --
CREATE TABLE join_table_1(id int, name char(4));
CREATE TABLE join_table_2(id int, age int);
CREATE TABLE join_table_3(id int, level int);
create table join_table_empty_1(id int, num_empty_1 int);
create table join_table_empty_2(id int, num_empty_2 int);
INSERT INTO join_table_1 VALUES (1, 'a');
INSERT INTO join_table_1 VALUES (2, 'b');
INSERT INTO join_table_1 VALUES (3, 'c');
INSERT INTO join_table_2 VALUES (1, 18);
INSERT INTO join_table_2 VALUES (2, 15);
INSERT INTO join_table_3 VALUES (1, 5);
INSERT INTO join_table_3 VALUES (3, 6);
*/