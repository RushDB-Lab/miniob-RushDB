/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "null_type.h"
#include "common/value.h"

int NullType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::NULLS, "left type is not a null");
  return -1;
}

RC NullType::to_string(const Value &val, string &result) const
{
  result = "NULL";
  return RC::SUCCESS;
}

RC NullType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  ASSERT(val.attr_type() == AttrType::NULLS, "val type is not a null");
  result.set_type(type);
  result.set_null();
  return RC::SUCCESS;
}
