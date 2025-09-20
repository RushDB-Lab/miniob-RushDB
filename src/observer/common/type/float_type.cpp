/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include <cmath>

#include "common/lang/comparator.h"
#include "common/lang/sstream.h"
#include "common/log/log.h"
#include "common/type/float_type.h"
#include "common/value.h"
#include "common/lang/limits.h"
#include "common/value.h"

int FloatType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::FLOATS, "left type is not integer");
  ASSERT(right.attr_type() == AttrType::INTS || right.attr_type() == AttrType::FLOATS, "right type is not numeric");
  float left_val  = left.get_float();
  float right_val = right.get_float();
  return common::compare_float((void *)&left_val, (void *)&right_val);
}

RC FloatType::add(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() + right.get_float());
  return RC::SUCCESS;
}
RC FloatType::subtract(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() - right.get_float());
  return RC::SUCCESS;
}
RC FloatType::multiply(const Value &left, const Value &right, Value &result) const
{
  result.set_float(left.get_float() * right.get_float());
  return RC::SUCCESS;
}

RC FloatType::divide(const Value &left, const Value &right, Value &result) const
{
  if (right.get_float() > -EPSILON && right.get_float() < EPSILON) {
    result.set_null();
    return RC::SUCCESS;
  }

  result.set_float(left.get_float() / right.get_float());
  return RC::SUCCESS;
}

RC FloatType::negative(const Value &val, Value &result) const
{
  result.set_float(-val.get_float());
  return RC::SUCCESS;
}

RC FloatType::set_value_from_str(Value &val, const string &data) const
{
  RC           rc = RC::SUCCESS;
  stringstream deserialize_stream;
  deserialize_stream.clear();
  deserialize_stream.str(data);

  float float_value;
  deserialize_stream >> float_value;
  if (!deserialize_stream || !deserialize_stream.eof()) {
    rc = RC::SCHEMA_FIELD_TYPE_MISMATCH;
  } else {
    val.set_float(float_value);
  }
  return rc;
}

RC FloatType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << common::double_to_str(val.value_.float_value_);
  result = ss.str();
  return RC::SUCCESS;
}

int FloatType::cast_cost(AttrType type)
{
  if (type == AttrType::FLOATS)
    return 0;  // FLOAT -> FLOAT
  // if (type == AttrType::INTS)
  //   return 1;  // FLOAT -> INT (可能丢失精度，也不支持转换)
  if (type == AttrType::BOOLEANS)
    return 1;        // FLOAT -> BOOL (非严格转换)
  return INT32_MAX;  // 不支持转换
}

RC FloatType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  switch (type) {
    case AttrType::FLOATS: {
      result.set_float(val.get_float());
    } break;
    case AttrType::INTS: {
      // 浮点数转整数（四舍五入，如1.3转换为1，1.5转换为2）
      // 涉及浮点数的比较，整数转换为浮点数，字符串转换为浮点数，再比较
      // 使用 std::round 进行四舍五入
      result.set_int(static_cast<int>(std::round(val.get_float())));
    } break;
    case AttrType::CHARS: {
      // 数字转字符串，不带符号，不考虑溢出
      // 浮点数的表示方法是什么?（举例：1.5转换为'1.5'）
      float       float_val = val.get_float();
      std::string str       = float_val < 0 ? std::to_string(-float_val) : std::to_string(float_val);
      // 去除尾随的0 和可能的 '.'
      str.erase(str.find_last_not_of('0') + 1, std::string::npos);
      if (str.back() == '.') {
        str.pop_back();
      }
      result.set_string(str.c_str());  // 设置字符串结果
    } break;
    case AttrType::BOOLEANS: {
      result.set_boolean(val.get_float() != 0.0f);  // 非零为 true，零为 false
    } break;
    default: return RC::UNSUPPORTED;  // 不支持的转换
  }
  return RC::SUCCESS;
}
