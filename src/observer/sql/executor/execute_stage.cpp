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
// Created by Longda on 2021/4/13.
//

#include <string>
#include <sstream>

#include "sql/executor/execute_stage.h"

#include "common/log/log.h"
#include "session/session.h"
#include "event/storage_event.h"
#include "event/sql_event.h"
#include "event/session_event.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/show_index.h"
#include "sql/stmt/stmt.h"
#include "sql/stmt/select_stmt.h"
#include "storage/default/default_handler.h"
#include "sql/executor/command_executor.h"
#include "sql/operator/calc_physical_operator.h"
#include "src/observer/storage/index/index.h"

using namespace std;
using namespace common;

RC ExecuteStage::handle_request(SQLStageEvent *sql_event)
{
  RC                                  rc                = RC::SUCCESS;
  const unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  if (physical_operator != nullptr) {
    return handle_request_with_physical_operator(sql_event);
  }

  SessionEvent *session_event = sql_event->session_event();

  Stmt *stmt = sql_event->stmt();
  if (stmt != nullptr) {
    CommandExecutor command_executor;
    rc = command_executor.execute(sql_event);
    session_event->sql_result()->set_return_code(rc);
  } else {
    return RC::INTERNAL;
  }
  return rc;
}

RC ExecuteStage::handle_request_with_physical_operator(SQLStageEvent *sql_event)
{
  RC rc = RC::SUCCESS;

  Stmt *stmt = sql_event->stmt();
  ASSERT(stmt != nullptr, "SQL Statement shouldn't be empty!");

  unique_ptr<PhysicalOperator> &physical_operator = sql_event->physical_operator();
  ASSERT(physical_operator != nullptr, "physical operator should not be null");

  // TODO 这里也可以优化一下，是否可以让physical operator自己设置tuple schema
  TupleSchema schema;  // schema——摘要
  SqlResult  *sql_result = sql_event->session_event()->sql_result();
  switch (stmt->type()) {
    case StmtType::SELECT: {
      SelectStmt *select_stmt     = static_cast<SelectStmt *>(stmt);
      bool        with_table_name = select_stmt->tables().size() > 1;
      // 处理聚合函数的名字
      if (select_stmt->agg_func().size() != 0) {
        sql_result->set_agg();
        for (auto temp : select_stmt->agg_func()) {
          string append_cell_;
          switch (temp.type) {
            case AGG_MAX: {
              append_cell_ = "MAX()";
              append_cell_.insert(append_cell_.begin() + 4,
                  temp.attributes.attribute_name.begin(),
                  temp.attributes.attribute_name.end());
            } break;
            case AGG_MIN: {
              append_cell_ = "MIN()";
              append_cell_.insert(append_cell_.begin() + 4,
                  temp.attributes.attribute_name.begin(),
                  temp.attributes.attribute_name.end());             
            } break;
            case AGG_SUM: {
              append_cell_ = "SUM()";
              append_cell_.insert(append_cell_.begin() + 4,
                  temp.attributes.attribute_name.begin(),
                  temp.attributes.attribute_name.end());
            } break;
            case AGG_AVG: {
              append_cell_ = "AVG()";
              append_cell_.insert(append_cell_.begin() + 4,
                  temp.attributes.attribute_name.begin(),
                  temp.attributes.attribute_name.end());
            } break;
            case AGG_COUNT: {
              append_cell_ = "COUNT()";
              append_cell_.insert(append_cell_.begin() + 6,
                  temp.attributes.attribute_name.begin(),
                  temp.attributes.attribute_name.end());
            } break;
            default: {
              return RC::FAILURE;
            }
          }
          schema.append_cell(append_cell_.c_str());
        }
        break;
      }

      for (const Field &field : select_stmt->query_fields()) {
        if (with_table_name) {
          schema.append_cell(field.table_name(), field.field_name());  // append cell 追加单元格
        } else {
          schema.append_cell(field.field_name());  // alias—— 文件别名
        }
      }
    } break;

    case StmtType::SHOW_INDEX: {
      ShowIndexStmt *show_index_stmt = static_cast<ShowIndexStmt *>(stmt);
      schema.append_cell("Table | Non_unique | Key_name | Seq_in_index | Column_name");
      sql_result->set_table(show_index_stmt->tables());
    } break;

    case StmtType::CALC: {
      CalcPhysicalOperator *calc_operator = static_cast<CalcPhysicalOperator *>(physical_operator.get());
      for (const unique_ptr<Expression> &expr : calc_operator->expressions()) {
        schema.append_cell(expr->name().c_str());
      }
    } break;

    case StmtType::EXPLAIN: {
      schema.append_cell("Query Plan");
    } break;
    default: {
      // 只有select返回结果
    } break;
  }

  sql_result->set_tuple_schema(schema);
  sql_result->set_operator(std::move(physical_operator));
  return rc;
}
