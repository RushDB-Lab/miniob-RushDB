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
  ASSERT(right.attr_type() == AttrType::NULLS, "right type is not a null");
  if (right.attr_type() == AttrType::NULLS) {
    return 0;
  }
  return INT32_MAX;
}

RC NullType::to_string(const Value &val, string &result) const
{
  result = "NULL";
  return RC::SUCCESS;
}

RC NullType::cast_to(const Value &val, AttrType type, Value &result) const
{
  ASSERT(val.attr_type() == AttrType::NULLS, "val type is not a null");
  switch (type) {
    case AttrType::UNDEFINED: {
      return RC::UNIMPLEMENTED;
    }
    case AttrType::CHARS: {
      result.set_string("");
      break;
    }
    case AttrType::INTS: {
      result.set_int(0);
      break;
    }
    case AttrType::FLOATS: {
      result.set_float(0.f);
      break;
    }
    case AttrType::BOOLEANS: {
      result.set_boolean(false);
      break;
    }
    case AttrType::DATES: {
      result.set_date(0);
      break;
    }
    case AttrType::NULLS: {
      result.set_null();
      break;
    }
    case AttrType::MAXTYPE: {
      return RC::UNIMPLEMENTED;
    }
    default: {
      return RC::UNIMPLEMENTED;
    }
  }
  return RC::SUCCESS;
}
