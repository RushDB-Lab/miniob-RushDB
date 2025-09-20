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

#include "sql/stmt/filter_stmt.h"
#include "common/lang/string.h"
#include "common/log/log.h"
#include "common/rc.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt() = default;

RC FilterStmt::create(Db *db, BaseTable *default_table, std::vector<std::string> tables_alias,
    std::unordered_map<std::string, BaseTable *> *tables, std::unique_ptr<Expression> &condition, FilterStmt *&stmt)
{
  RC rc = RC::SUCCESS;
  stmt  = nullptr;
  // 1、 没有条件直接返回
  if (nullptr == condition) {
    return rc;
  }

  // 2、 检查条件的合法性
  vector<unique_ptr<Expression>> cond_expressions;
  BinderContext                  binder_context;

  if (tables != nullptr) {
    for (const auto &i : *tables) {
      binder_context.add_table(i.second);
    }
  }
  binder_context.add_db(db);
  binder_context.set_alias(std::move(tables_alias));
  binder_context.set_tables(tables);
  binder_context.set_default_table(default_table);
  ExpressionBinder expression_binder(binder_context);

  rc = expression_binder.bind_expression(condition, cond_expressions);

  if (OB_FAIL(rc)) {
    LOG_WARN("CAN NOT PASS CONDITION CHECK!");
    return rc;
  }
  FilterStmt *tmp_stmt = new FilterStmt();
  tmp_stmt->condition_ = std::move(cond_expressions[0]);

  stmt = tmp_stmt;
  return rc;
}
