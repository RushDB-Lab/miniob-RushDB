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
// Created by WangYunlai on 2021/6/9.
//

#include "sql/operator/insert_physical_operator.h"
#include "sql/stmt/insert_stmt.h"
#include "storage/table/table.h"
#include "storage/trx/trx.h"

InsertPhysicalOperator::InsertPhysicalOperator(BaseTable *table, const std::vector<std::vector<Value>> &values_list)
    : table_(table), values_list_(values_list)
{}

RC InsertPhysicalOperator::open(Trx *trx)
{
  RC                  rc;
  std::vector<Record> records(values_list_.size());
  for (size_t i = 0; i < values_list_.size(); ++i) {
    rc = table_->make_record(static_cast<int>(values_list_[i].size()), values_list_[i].data(), records[i]);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      return rc;
    }
  }

  int size = static_cast<int>(records.size());
  for (int i = 0; i < size; ++i) {
    rc = trx->insert_record(table_, records[i]);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to insert record by transaction. rc=%s", strrc(rc));
      // 要么都插入成功，要么都不插入
      LOG_INFO("Rolling back previously inserted records up to index %d", i - 1);
      while (--i >= 0) {
        // 删除之前插入成功的
        RC rc2 = trx->delete_record(table_, records[i]);
        if (rc2 != RC::SUCCESS) {
          LOG_WARN("failed to delete record by transaction. rc=%s", strrc(rc2));
        } else {
          LOG_INFO("Successfully deleted record at index %d", i);
        }
      }
      return rc;
    }
  }

  return rc;
}

RC InsertPhysicalOperator::next() { return RC::RECORD_EOF; }

RC InsertPhysicalOperator::close() { return RC::SUCCESS; }
