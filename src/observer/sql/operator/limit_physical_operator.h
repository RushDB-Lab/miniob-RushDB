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
// Created by HuXin on 24-10-9.
//

#include "sql/operator/physical_operator.h"
#include "sql/expr/tuple.h"
#include <functional>
#include <queue>

class LimitPhysicalOperator : public PhysicalOperator
{
public:
  LimitPhysicalOperator(int limit) : limit_(limit) {}

  virtual ~LimitPhysicalOperator() = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::LIMIT; }

  int limit() const { return limit_; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override;

private:
  int pos_ = 0;
  int limit_;
};
