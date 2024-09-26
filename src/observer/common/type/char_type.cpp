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
#include "common/log/log.h"
#include "common/type/char_type.h"
#include "common/value.h"

static int y, m, d;

static bool check_date(int y, int m, int d)
{
  // 定义每个月的天数
  static int mon[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
  // 判断是否为闰年
  bool leap = (y % 400 == 0) || (y % 100 != 0 && y % 4 == 0);
  // 检查年份、月份和日期的合法性
  return (y > 0 && y <= 9999) && (m > 0 && m <= 12) &&
         (d > 0 && d <= (mon[m] + (m == 2 && leap ? 1 : 0)));  // 2月如果是闰年则加1天
}

static RC parse_date(const char *str, int &result)
{
  if (sscanf(str, "%d-%d-%d", &y, &m, &d) != 3) {
    return RC::INVALID_ARGUMENT;
  }
  if (!check_date(y, m, d)) {
    return RC::INVALID_ARGUMENT;
  }
  result = y * 10000 + m * 100 + d;
  return RC::SUCCESS;
}

static RC parse_float_prefix(const char *str, float &result)
{
  char *end_ptr;
  // 输入不是有效的整数格式，会转换为 0.0
  double float_val = std::strtod(str, &end_ptr);
  // 注释以支持前缀解析
  // if (*end_ptr != '\0' && !isspace(*end_ptr)) {
  //   return RC::INVALID_ARGUMENT;  // 浮点数后应为结尾或空白字符
  // }
  // 默认认为 float_val 是否在 float 范围内
  result = static_cast<float>(float_val);
  return RC::SUCCESS;
}

int CharType::compare(const Value &left, const Value &right) const
{
  ASSERT(left.attr_type() == AttrType::CHARS && right.attr_type() == AttrType::CHARS, "invalid type");
  return common::compare_string(
      (void *)left.value_.pointer_value_, left.length_, (void *)right.value_.pointer_value_, right.length_);
}

RC CharType::set_value_from_str(Value &val, const string &data) const
{
  val.set_string(data.c_str());
  return RC::SUCCESS;
}

RC CharType::cast_to(const Value &val, AttrType type, Value &result) const
{
  switch (type) {
    case AttrType::DATES: {
      int date_val;
      RC  rc = parse_date(val.value_.pointer_value_, date_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_date(date_val);
    } break;
    // 字符串转数字
    //  如果字符串刚好是一个数字，则转换为对应的数字（如'1'转换为1，'2.1'转换为2.1）
    //  如果字符串的前缀是一个数字，则转换前缀数字部分为数字（如'1a1'转换为1，'2.1a'转换为2.1）
    //  如果字符串前缀不是任何合法的数字，则转换为0（不需要考虑前导符号 '+' '-'）
    //  如果转换数字溢出怎么处理?（不考虑）
    //  是否考虑十六进制/八进制?（不考虑）
    case AttrType::INTS: {
      // WHERE id < '1.5a';
      // 先当浮点数解析，浮点数可以兼容整型，再四舍五入转 int
      float float_val;
      RC    rc = parse_float_prefix(val.value_.pointer_value_, float_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      int int_val = static_cast<int>(float_val);
      // 是整数
      if (int_val == float_val) {
        result.set_int(int_val);
      } else {
        // 为浮点数，类型提升
        result.set_float(float_val);
      }
    } break;
    case AttrType::FLOATS: {
      float float_val;
      RC    rc = parse_float_prefix(val.value_.pointer_value_, float_val);
      if (rc != RC::SUCCESS) {
        return rc;
      }
      result.set_float(float_val);
    } break;
    default:
      return RC::UNIMPLEMENTED;
  }
  return RC::SUCCESS;
}

int CharType::cast_cost(AttrType type)
{
  if (type == AttrType::CHARS) {
    return 0;
  }
  if (type == AttrType::DATES) {
    return 1;
  }
  if (type == AttrType::INTS) {
    return 1;
  }
  if (type == AttrType::FLOATS) {
    return 1;
  }
  return INT32_MAX;
}

RC CharType::to_string(const Value &val, string &result) const
{
  stringstream ss;
  ss << val.value_.pointer_value_;
  result = ss.str();
  return RC::SUCCESS;
}
