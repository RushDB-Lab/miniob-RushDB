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
// Created by Wangyunlai 2023/6/27
//

#pragma once

#include "common/rc.h"
#include <cstdint>
#include <string>
#include <regex>

/**
 * @brief 属性的类型
 *
 */
enum AttrType
{
  UNDEFINED,
  CHARS,       ///< 字符串类型
  INTS,        ///< 整数类型(4字节)
  DATES,       ///< 日期类型(4字节)
  null,        ///< 空NULL类型
  FLOATS,      ///< 浮点数类型(4字节)
  BOOLEANS,    ///< boolean类型，当前不是由parser解析出来的，是程序内部使用的
  LIKE_REGEX,  /// like的正则表达式类
};
const char *attr_type_to_string(AttrType type);
AttrType    attr_type_from_string(const char *s);

/**
 * @brief 属性的值
 *
 */
class Value
{
public:
  Value() = default;

  Value(AttrType attr_type, char *data, int length = 4) : attr_type_(attr_type) { this->set_data(data, length); }

  explicit Value(int val);
  explicit Value(float val);
  explicit Value(bool val);
  explicit Value(const char *s, int len = 0);

  Value(const Value &other)            = default;
  Value &operator=(const Value &other) = default;

  void        set_type(AttrType type) { this->attr_type_ = type; }
  void        set_data(char *data, int length);
  void        set_data(const char *data, int length) { this->set_data(const_cast<char *>(data), length); }
  void        set_int(int val);
  void        set_float(float val);
  void        set_boolean(bool val);
  void        set_string(const char *s, int len = 0);
  void        set_value(const Value &value);
  void        set_null();
  std::string int32_to_str(int32_t val) const;

  std::string to_string() const;

  int compare(const Value &other) const;

  int char_to_int32() const;
  RC  char_to_int(std::string num_str) const;
  RC  char_to_float(std::string float_str) const;
  RC  num_to_char() const;
  RC  float_to_char() const;
  RC  int_to_float() const;
  RC  float_to_int() const;

  bool cheak_date(int32_t date) const;

  static bool is_num(const char c);

  static int is_date(const char *date);

  const char *data() const;
  int         length() const { return length_; }

  AttrType attr_type() const { return attr_type_; }

public:
  /**
   * 获取对应的值
   * 如果当前的类型与期望获取的类型不符，就会执行转换操作
   */
  int         get_int() const;
  float       get_float() const;
  std::string get_string() const;
  bool        get_boolean() const;
  RC          to_regex(std::string regex) const;
  static bool matchString(const std::string &pattern, const std::string &str);

private:
  AttrType attr_type_ = UNDEFINED;
  int      length_    = 0;
  int      date_case  = 0;

  union
  {
    int     int_value_;
    float   float_value_;
    bool    bool_value_;
    int32_t date_value_;
  } num_value_;
  std::string str_value_;
};