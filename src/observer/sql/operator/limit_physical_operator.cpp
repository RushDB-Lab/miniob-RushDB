/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "limit_physical_operator.h"

RC LimitPhysicalOperator::open(Trx *trx) { return children_[0]->open(trx); }

RC LimitPhysicalOperator::next()
{
  if (pos_ == limit_) {
    return RC::RECORD_EOF;
  }
  pos_++;
  return children_[0]->next();
}

RC LimitPhysicalOperator::close() { return children_[0]->close(); }

Tuple *LimitPhysicalOperator::current_tuple() { return children_[0]->current_tuple(); }
