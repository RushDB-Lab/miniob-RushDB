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

class STD
{
public:
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
    if (args[0].attr_type() != AttrType::DATES && args[0].attr_type() != AttrType::CHARS) {
      return RC::INVALID_ARGUMENT;
    }
    if (args[1].attr_type() != AttrType::CHARS) {
      return RC::INVALID_ARGUMENT;
    }

    int year, month, day;

    if (args[0].attr_type() == AttrType::DATES) {
      // 提取年、月、日（假设日期格式为YYYYMMDD）
      int val = args[0].get_int();
      year    = val / 10000;        // 获取年份
      month   = (val / 100) % 100;  // 获取月份
      day     = val % 100;          // 获取日期
    }

    if (args[0].attr_type() == AttrType::CHARS) {
      // 日期格式假设为 '2019-9-17' 或 '2019-09-17'
      std::string date_str = args[0].to_string();
      sscanf(date_str.c_str(), "%d-%d-%d", &year, &month, &day);
    }

    auto fmt = args[1].to_string();

    string str;

    // 遍历格式字符串，并替换格式符
    for (size_t i = 0; i < fmt.length(); ++i) {
      if (fmt[i] == '%' && i + 1 < fmt.length()) {
        switch (fmt[i + 1]) {
          case 'Y':  // 四位数年份
            str += std::to_string(year);
            break;
          case 'y':  // 两位数年份
            str += std::to_string(year).substr(2, 2);
            break;
          case 'm':  // 两位数月份
            str += (month < 10 ? "0" : "") + std::to_string(month);
            break;
          case 'c':  // 不带前导零的月份
            str += std::to_string(month);
            break;
          case 'M':  // 完整的月份名称
            str += get_full_month_name(month);
            break;
          case 'd':  // 两位数日期
            str += (day < 10 ? "0" : "") + std::to_string(day);
            break;
          case 'e':  // 不带前导零的日期
            str += std::to_string(day);
            break;
          case 'D':  // 带序数后缀的日期
            str += get_day_with_suffix(day);
            break;
          default:  // 未知格式符，按原样输出
            str += fmt[i];
            str += fmt[i + 1];
            break;
        }
        ++i;  // 跳过格式符的下一个字符
      } else {
        str += fmt[i];  // 普通字符直接追加
      }
    }

    result = Value(str.c_str());
    return RC::SUCCESS;
  }

private:
  static inline string get_day_with_suffix(int day)
  {
    if (day >= 11 && day <= 13) {
      return std::to_string(day) + "th";
    }
    switch (day % 10) {
      case 1: {
        return std::to_string(day) + "st";
      }
      case 2: {
        return std::to_string(day) + "nd";
      }
      case 3: {
        return std::to_string(day) + "rd";
      }
      default: {
        return std::to_string(day) + "th";
      }
    }
  }

  static inline string get_full_month_name(int month)
  {
    switch (month) {
      case 1: return "January";
      case 2: return "February";
      case 3: return "March";
      case 4: return "April";
      case 5: return "May";
      case 6: return "June";
      case 7: return "July";
      case 8: return "August";
      case 9: return "September";
      case 10: return "October";
      case 11: return "November";
      case 12: return "December";
      default: return "";  // 如果月份值无效，返回一个错误字符串
    }
  }
};
