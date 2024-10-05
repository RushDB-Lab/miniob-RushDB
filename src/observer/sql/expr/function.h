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

#include "common/value.h"
#include <cmath>

namespace STD {

static inline RC LENGTH(const vector<Value> &args, Value &result)
{
  if (args.size() != 1) {
    return RC::INVALID_ARGUMENT;
  }
  if (args[0].attr_type() != AttrType::CHARS) {
    return RC::INVALID_ARGUMENT;
  }
  int length = static_cast<int>(args[0].to_string().size());
  result     = Value(length);
  return RC::SUCCESS;
}

static inline RC ROUND(const vector<Value> &args, Value &result)
{
  if (args.size() != 1 && args.size() != 2) {
    return RC::INVALID_ARGUMENT;
  }
  float number;
  int   decimals = 0;  // 默认四舍五入为整数
  if (args[0].attr_type() != AttrType::FLOATS) {
    return RC::INVALID_ARGUMENT;
  }
  if (args.size() == 2) {
    if (args[1].attr_type() != AttrType::INTS) {
      return RC::INVALID_ARGUMENT;
    }
    decimals = args[1].get_int();
  }
  number       = args[0].get_float();
  float factor = std::pow(10.f, static_cast<float>(decimals));
  float round  = std::round(number * factor) / factor;
  result       = Value(round);
  return RC::SUCCESS;
}

static inline RC DATE_FORMAT(const vector<Value> &args, Value &result)
{
  if (args.size() != 2) {
    return RC::INVALID_ARGUMENT;
  }
  if (args[0].attr_type() != AttrType::DATES) {
    return RC::INVALID_ARGUMENT;
  }
  if (args[1].attr_type() != AttrType::CHARS) {
    return RC::INVALID_ARGUMENT;
  }

  // TODO: DATE_FORMAT
  return RC::SUCCESS;
}

}  // namespace STD