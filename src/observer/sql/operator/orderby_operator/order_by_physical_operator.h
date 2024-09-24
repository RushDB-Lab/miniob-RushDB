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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "sql/expr/tuple.h"
#include "sql/operator/physical_operator.h"
#include "sql/stmt/select_stmt.h"
#include "storage/record/record_manager.h"
#include "src/observer/sql/operator/orderby_operator/order_by_compator.h"
#include "common/rc.h"

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class OrderByPhysicalOperator : public PhysicalOperator
{
public:
  friend class Campator;
  RC init_compator(std::vector<orderby> OrderBys);
  OrderByPhysicalOperator() {}

  virtual ~OrderByPhysicalOperator() = default;

  std::string param() const override;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::ORDER_BY; }
  bool                 Compare(const Tuple *first, const Tuple *second);
  RC                   open(Trx *trx) override;
  RC                   next() override;
  RC                   close() override;

  Tuple *current_tuple() override;

private:
  Table                     *table_   = nullptr;
  bool                       is_join  = false;
  Trx                       *trx_     = nullptr;
  Campator                  *campator = nullptr;
  std::vector<const Tuple *> tuples;
  std::vector<orderby>       OrderBys;
  int                        index = 0;
  Record                     current_record_;
  RowTuple                   tuple_;
  //std::recursive_mutex       lock;  // 递归锁作为成员变量
};
