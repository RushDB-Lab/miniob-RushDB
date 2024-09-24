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

#include "src/observer/sql/operator/orderby_operator/order_by_physical_operator.h"
#include "sql/expr/tuple.h"
#include "sql/operator/orderby_operator/order_by_compator.h"
#include "storage/table/table.h"
#include "event/sql_debug.h"
#include <algorithm>
#include <execution>
#include <memory>

using namespace std;

RC OrderByPhysicalOperator::open(Trx *trx)
{
  RC rc = RC::SUCCESS;
  rc    = children_[0]->open(trx);
  if (rc != RC::SUCCESS)
    return RC::FAILURE;
  while (rc == RC::SUCCESS) {
    rc                     = RC::SUCCESS;
    PhysicalOperator *oper = children_.front().get();
    while (RC::SUCCESS == (rc = oper->next())) {
      const Tuple *tuple = (oper->current_tuple())->clone();
      // std::cout << oper->current_tuple()->to_string() << std::endl;
      if (nullptr == tuple) {
        rc = RC::INTERNAL;
        LOG_WARN("failed to get tuple from operator");
        break;
      } else if (tuple->cell_num() == 0) {
        continue;
      }
      tuples.push_back(tuple);
    }
  }
  trx_ = trx;
  std::sort(std::execution::par, tuples.begin(), tuples.end(), [this](const Tuple *first, const Tuple *second) {
    return campator->compare(first, second);
  });
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::next()
{
  if (index >= tuples.size()) {
    return RC::RECORD_EOF;
  } else if (index < 0) {
    return RC::FAILURE;
  }
  return RC::SUCCESS;
}

RC OrderByPhysicalOperator::close()
{
  Campator *now = campator, *next = campator;
  while (now != nullptr) {
    next = now->child_compator;
    delete now;
    now = next;
  }
  return RC::SUCCESS;
}

Tuple *OrderByPhysicalOperator::current_tuple() { return const_cast<Tuple *>(tuples[index++]); }

string OrderByPhysicalOperator::param() const { return table_->name(); }
RC     OrderByPhysicalOperator::init_compator(std::vector<orderby> OrderBys)
{
  this->OrderBys = OrderBys;
  int size = OrderBys.size(), index = 0;
  if (!size) {
    return RC::FAILURE;
  }
  campator      = new Campator(OrderBys[index++]);
  Campator *now = campator, *temp;

  while (index < size) {
    temp                = new Campator(OrderBys[index++]);
    now->child_compator = temp;
    now                 = now->child_compator;
  }
  return RC::SUCCESS;
}

inline bool OrderByPhysicalOperator::Compare(const Tuple *first, const Tuple *second)
{
  //lock.lock();

  return campator->compare(first, second);
  //lock.unlock();
}