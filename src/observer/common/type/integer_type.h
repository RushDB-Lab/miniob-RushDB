/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/type/data_type.h"

#include <common/value.h>

/**
 * @brief 整型类型
 * @ingroup DataType
 */
class IntegerType : public DataType
{
public:
           IntegerType() : DataType(AttrType::INTS) {}
  virtual ~IntegerType() {}

  int compare(const Value &left, const Value &right) const override;

  RC add(const Value &left, const Value &right, Value &result) const override;
  RC subtract(const Value &left, const Value &right, Value &result) const override;
  RC multiply(const Value &left, const Value &right, Value &result) const override;
  RC negative(const Value &val, Value &result) const override;

  RC set_value_from_str(Value &val, const string &data) const override;

  RC to_string(const Value &val, string &result) const override;

  int cast_cost(AttrType type) override
  {
    if (type == AttrType::INTS)
      return 0;  // INT -> INT
    if (type == AttrType::FLOATS)
      return 1;  // INT -> FLOAT
    if (type == AttrType::BOOLEANS)
      return 1;        // INT -> BOOL (非严格转换)
    return INT32_MAX;  // 不支持转换
  }
  RC cast_to(const Value &val, AttrType type, Value &result) const override
  {
    if (type == AttrType::INTS) {
      result.set_int(val.get_int());
      return RC::SUCCESS;
    } else if (type == AttrType::FLOATS) {
      result.set_float(static_cast<float>(val.get_int()));  // 转换为浮点数
      return RC::SUCCESS;
    } else if (type == AttrType::BOOLEANS) {
      result.set_boolean(val.get_int() != 0);  // 0 为 false，其他为 true
      return RC::SUCCESS;
    }
    return RC::UNSUPPORTED;  // 不支持的转换
  }
};