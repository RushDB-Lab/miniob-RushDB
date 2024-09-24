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
// Created by WangYunlai on 2023/06/28.
//

#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <sstream>
#include <string>
#include "sql/parser/value.h"
#include "storage/field/field.h"
#include "common/log/log.h"
#include "common/lang/comparator.h"
#include "common/lang/string.h"

const char *ATTR_TYPE_NAME[] = {"undefined", "chars", "ints", "dates", "NULL", "floats", "booleans", "like_regex"};

const char *attr_type_to_string(AttrType type)
{
  if (type >= UNDEFINED && type <= FLOATS) {
    return ATTR_TYPE_NAME[type];
  }
  return "unknown";
}
AttrType attr_type_from_string(const char *s)
{
  for (unsigned int i = 0; i < sizeof(ATTR_TYPE_NAME) / sizeof(ATTR_TYPE_NAME[0]); i++) {
    if (0 == strcmp(ATTR_TYPE_NAME[i], s)) {
      return (AttrType)i;
    }
  }
  return UNDEFINED;
}

Value::Value(int val) { set_int(val); }

Value::Value(float val) { set_float(val); }

Value::Value(bool val) { set_boolean(val); }

Value::Value(const char *s, int len /*= 0*/)
{
  if (!strcmp(s, "null")) {
    set_null();
    return;
  } else
    set_string(s, len);
}

void Value::set_data(char *data, int length)
{
  if (std::memcmp(data, "null", 4) == 0) {
    attr_type_ = null;
  }
  switch (attr_type_) {
    case CHARS: {
      set_string(data, length);
    } break;
    case INTS: {
      num_value_.int_value_ = *(int *)data;
      length_               = length;
    } break;
    case FLOATS: {
      num_value_.float_value_ = *(float *)data;
      length_                 = length;
    } break;
    case BOOLEANS: {
      num_value_.bool_value_ = *(int *)data != 0;
      length_                = length;
    } break;
    case DATES: {
      num_value_.date_value_ = *(int32_t *)data;
      length_                = length;
    }
    case null: {
      str_value_.assign("null");
      length_ = 4;
    } break;
    default: {
      LOG_WARN("unknown data type: %d", attr_type_);
    } break;
  }
}
void Value::set_int(int val)
{
  attr_type_            = INTS;
  num_value_.int_value_ = val;
  length_               = sizeof(val);
}

void Value::set_float(float val)
{
  attr_type_              = FLOATS;
  num_value_.float_value_ = val;
  length_                 = sizeof(val);
}
void Value::set_boolean(bool val)
{
  attr_type_             = BOOLEANS;
  num_value_.bool_value_ = val;
  length_                = sizeof(val);
}
void Value::set_string(const char *s, int len /*= 0*/)
{
  attr_type_ = CHARS;
  if (len > 0) {
    len = strnlen(s, len);
    str_value_.assign(s, len);
  } else {
    str_value_.assign(s);
  }
  length_ = str_value_.length();
}

void Value::set_null()
{

  attr_type_ = null;
  str_value_.assign("null");
  length_ = 4;
}

void Value::set_value(const Value &value)
{
  switch (value.attr_type_) {
    case INTS: {
      set_int(value.get_int());
    } break;
    case FLOATS: {
      set_float(value.get_float());
    } break;
    case CHARS: {
      set_string(value.get_string().c_str());
    } break;
    case BOOLEANS: {
      set_boolean(value.get_boolean());
    } break;
    case DATES: {
      attr_type_             = DATES;
      num_value_.date_value_ = value.num_value_.date_value_;
      length_                = sizeof(num_value_.date_value_);
    }
    case LIKE_REGEX: {
      ASSERT(false, "REGEX can not be output!");
    } break;
    case UNDEFINED: {
      ASSERT(false, "got an invalid value type");
    } break;
  }
}

const char *Value::data() const
{
  switch (attr_type_) {
    case CHARS: {
      return str_value_.c_str();
    } break;
    case LIKE_REGEX: {
      return str_value_.c_str();
    } break;
    case null: {
      return str_value_.c_str();
    } break;
    default: {
      return (const char *)&num_value_;
    } break;
  }
}

std::string Value::to_string() const
{
  std::stringstream os;
  switch (attr_type_) {
    case INTS: {
      os << num_value_.int_value_;
    } break;
    case FLOATS: {
      os << common::double_to_str(num_value_.float_value_);
    } break;
    case BOOLEANS: {
      os << num_value_.bool_value_;
    } break;
    case CHARS: {
      os << str_value_;
    } break;
    case DATES: {
      os << int32_to_str(num_value_.date_value_);
    } break;
    case LIKE_REGEX: {
      os << str_value_;
    } break;
    case null: {
      os << "null";
    } break;
    default: {
      LOG_WARN("unsupported attr type: %d", attr_type_);
    } break;
  }
  return os.str();
}

std::string Value::int32_to_str(int32_t val) const
{
  std::string base = std::to_string(val);
  base.insert(base.begin() + 4, '-');
  base.insert(base.begin() + 7, '-');
  return base;
}

int Value::compare(const Value &other) const
{
  if (this->attr_type_ == other.attr_type_) {
    switch (this->attr_type_) {
      case INTS: {
        return common::compare_int((void *)&this->num_value_.int_value_, (void *)&other.num_value_.int_value_);
      } break;
      case FLOATS: {
        return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other.num_value_.float_value_);
      } break;
      case CHARS: {
        return common::compare_string((void *)this->str_value_.c_str(),
            this->str_value_.length(),
            (void *)other.str_value_.c_str(),
            other.str_value_.length());
      } break;
      case BOOLEANS: {
        return common::compare_int((void *)&this->num_value_.bool_value_, (void *)&other.num_value_.bool_value_);
      } break;
      case DATES: {
        return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
      } break;
      case null: {
        return 0;
      } break;
      default: {
        LOG_WARN("unsupported type: %d", this->attr_type_);
      }
    }
  } else if (this->attr_type_ == INTS && other.attr_type_ == FLOATS) {
    float this_data = this->num_value_.int_value_;
    return common::compare_float((void *)&this_data, (void *)&other.num_value_.float_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == INTS) {
    float other_data = other.num_value_.int_value_;
    return common::compare_float((void *)&this->num_value_.float_value_, (void *)&other_data);
  } else if (this->attr_type_ == DATES && other.attr_type_ == CHARS) {
    other.char_to_int32();
    return common::compare_int((void *)&this->num_value_.date_value_, (void *)&other.num_value_.date_value_);
  } else if (other.attr_type_ == DATES && this->attr_type_ == CHARS) {
    this->char_to_int32();
    return common::compare_int((void *)&other.num_value_.date_value_, (void *)&this->num_value_.date_value_);
  } else if (this->attr_type_ == FLOATS && other.attr_type_ == CHARS) {
    return -common::compare_char_with_num((void *)other.str_value_.c_str(), (void *)&num_value_.float_value_, 2);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == FLOATS) {
    return common::compare_char_with_num((void *)this->str_value_.c_str(), (void *)&other.num_value_.float_value_, 2);
  } else if (this->attr_type_ == CHARS && other.attr_type_ == INTS) {
    return common::compare_char_with_num((void *)this->str_value_.c_str(), (void *)&other.num_value_.int_value_, 1);
  } else if (this->attr_type_ == INTS && other.attr_type_ == CHARS) {
    return -common::compare_char_with_num((void *)other.str_value_.c_str(), (void *)&num_value_.int_value_, 1);
  } else if (this->attr_type_ == null && other.attr_type_ != null) {
    return -1;
  } else if (this->attr_type_ != null && other.attr_type_ == null) {
    return 1;
  } else if (this->attr_type_ == null && other.attr_type_ == null) {
    return 0;
  }
  // 0是char，1是int，2是float
  else if (this->attr_type_ == LIKE_REGEX || other.attr_type_ != LIKE_REGEX) {
    if (other.attr_type_ == CHARS)
      return common::compare_with_regex((void *)this->str_value_.c_str(), (void *)other.to_string().c_str(), 0);
    if (other.attr_type_ == INTS)
      return common::compare_with_regex((void *)this->str_value_.c_str(), (void *)&num_value_.int_value_, 1);
    if (other.attr_type_ == FLOATS)
      return common::compare_with_regex((void *)this->str_value_.c_str(), (void *)&other.num_value_.float_value_, 2);
  } else if (this->attr_type_ != LIKE_REGEX || other.attr_type_ == LIKE_REGEX) {

    if (this->attr_type_ == CHARS)
      return common::compare_with_regex((void *)other.to_string().c_str(), (void *)this->str_value_.c_str(), 0);
    if (this->attr_type_ == INTS)
      return common::compare_with_regex((void *)other.to_string().c_str(), (void *)&this->num_value_.int_value_, 1);
    if (this->attr_type_ == FLOATS)
      return common::compare_with_regex((void *)other.to_string().c_str(), (void *)&this->num_value_.float_value_, 2);
  }
  LOG_WARN("not supported");
  return -1;  // TODO return rc?
}

int Value::get_int() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return (int)(std::stol(str_value_));
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to number. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0;
      }
    }
    case INTS: {
      return num_value_.int_value_;
    }
    case FLOATS: {
      return (int)(num_value_.float_value_);
    }
    case BOOLEANS: {
      return (int)(num_value_.bool_value_);
    }
    case DATES: {
      return num_value_.int_value_;
    } break;
    case null: {
      return 0;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

float Value::get_float() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        return std::stof(str_value_);
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return 0.0;
      }
    } break;
    case INTS: {
      return float(num_value_.int_value_);
    } break;
    case FLOATS: {
      return num_value_.float_value_;
    } break;
    case BOOLEANS: {
      return float(num_value_.bool_value_);
    } break;
    case DATES: {
      return float(num_value_.int_value_);
    } break;
    case null: {
      return 0.0;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return 0;
    }
  }
  return 0;
}

std::string Value::get_string() const { return this->to_string(); }

bool Value::get_boolean() const
{
  switch (attr_type_) {
    case CHARS: {
      try {
        float val = std::stof(str_value_);
        if (val >= EPSILON || val <= -EPSILON) {
          return true;
        }

        int int_val = std::stol(str_value_);
        if (int_val != 0) {
          return true;
        }

        return !str_value_.empty();
      } catch (std::exception const &ex) {
        LOG_TRACE("failed to convert string to float or integer. s=%s, ex=%s", str_value_.c_str(), ex.what());
        return !str_value_.empty();
      }
    } break;
    case INTS: {
      return num_value_.int_value_ != 0;
    } break;
    case FLOATS: {
      float val = num_value_.float_value_;
      return val >= EPSILON || val <= -EPSILON;
    } break;
    case BOOLEANS: {
      return num_value_.bool_value_;
    } break;
    case DATES: {
      return num_value_.int_value_ != 0;
    } break;
    default: {
      LOG_WARN("unknown data type. type=%d", attr_type_);
      return false;
    }
  }
  return false;
}

bool Value::is_num(const char c) { return c >= '0' && c <= '9'; }

int32_t convertToEightDigit(const std::string &dateStr)
{
  std::string year, month, day;
  char        delimiter;

  std::istringstream iss(dateStr);
  iss >> year >> delimiter >> month >> delimiter >> day;

  int32_t result = std::stoi(year) * 10000 + std::stoi(month) * 100 + std::stoi(day);

  return result;
}

int Value::is_date(const char *date)
{
  std::string date1(date);
  std::regex  pattern(R"(\b\d{4}-\d{1,2}-\d{1,2}\b)");
  std::smatch match;
  return std::regex_match(date1, match, pattern);
}

bool Value::cheak_date(int32_t date) const
{
  int year  = date / 10000;
  int month = (date / 100) % 100;
  int day   = date % 100;

  if (year < 1 || year > 9999)
    return false;
  if (month < 1 || month > 12)
    return false;
  if (day < 1 || day > 31)
    return false;

  // 检查月份对应的天数
  if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30)
    return false;
  if (month == 2) {
    if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
      if (day > 29)
        return false;
    } else {
      if (day > 28)
        return false;
    }
  }
  return true;
}

int Value::char_to_int32() const
{
  int year, month, day;
  sscanf(this->str_value_.c_str(), "%d-%d-%d", &year, &month, &day);
  *(int32_t *)(&num_value_.date_value_) = year * 10000 + month * 100 + day;
  if (!cheak_date(num_value_.date_value_))
    return 0;
  AttrType *att        = (AttrType *)(&(this->attr_type_));
  *att                 = DATES;
  *(int *)(&(length_)) = sizeof(int32_t);
  return 1;
}

int convertToInt(const std::string &str)
{
  try {
    return std::stoi(str);
  } catch (const std::exception &e) {
    LOG_WARN("Failed to convert string to int: %s",
          e.what());
    // 返回默认值或采取其他错误处理措施
    return -1;
  }
}

RC Value::char_to_int(std::string num_str) const
{
  RC rc = RC::SUCCESS;
  if (num_str.size() != 0) {
    int num = (int)convertToInt(num_str);
    if (num == -1)
      return RC::FAILURE;
    *(int *)(&(num_value_.int_value_)) = num;

  } else {
    *(int *)(&(num_value_.int_value_)) = 0;
  }
  AttrType *att        = (AttrType *)(&(this->attr_type_));
  *att                 = INTS;
  *(int *)(&(length_)) = sizeof(int);
  return rc;
}

RC Value::char_to_float(std::string float_str) const
{
  RC rc = RC::SUCCESS;
  if (float_str.size() != 0) {
    float num                              = std::stof(float_str);
    *(float *)(&(num_value_.float_value_)) = num;

  } else {
    *(float *)(&(num_value_.float_value_)) = 0;
  }
  AttrType *att        = (AttrType *)(&(this->attr_type_));
  *att                 = FLOATS;
  *(int *)(&(length_)) = sizeof(float);
  return rc;
}
RC Value::num_to_char() const
{
  *(std::string *)(&(str_value_)) = std::to_string(num_value_.int_value_);
  AttrType *att                   = (AttrType *)(&(this->attr_type_));
  *att                            = CHARS;
  *(int *)(&(length_))            = str_value_.size();
  return RC::SUCCESS;
}

RC Value::float_to_char() const
{
  std::string str = std::to_string(num_value_.float_value_);
  str.erase(str.find_last_not_of('0') + 1, std::string::npos);
  *(std::string *)(&(str_value_)) = str;
  AttrType *att                   = (AttrType *)(&(this->attr_type_));
  *att                            = CHARS;
  *(int *)(&(length_))            = str_value_.size();
  return RC::SUCCESS;
}

RC Value::int_to_float() const
{
  *(float *)(&(num_value_.float_value_)) = (float)num_value_.int_value_;
  AttrType *att                          = (AttrType *)(&(this->attr_type_));
  *att                                   = FLOATS;
  *(int *)(&(length_))                   = sizeof(float);
  return RC::SUCCESS;
}

RC Value::float_to_int() const
{
  *(int *)(&(num_value_.int_value_)) = static_cast<int>(std::round(num_value_.float_value_));
  AttrType *att                      = (AttrType *)(&(this->attr_type_));
  *att                               = INTS;
  *(int *)(&(length_))               = sizeof(int);
  return RC::SUCCESS;
}
std::string extractCharacters(const std::string &inputString)
{
  std::string extractedCharacters;
  bool        insideQuotes = false;

  for (char c : inputString) {
    if (c == '\'' || c == '\"') {
      insideQuotes = !insideQuotes;  // 切换引号状态
    } else if (insideQuotes) {
      extractedCharacters += c;  // 如果在引号内，将字符添加到提取的字符串中
    }
  }

  return extractedCharacters;
}

bool Value::matchString(const std::string &pattern, const std::string &str)
{
  size_t patternIndex  = 0;
  size_t strIndex      = 0;
  size_t patternLen    = pattern.length();
  size_t strLen        = str.length();
  size_t matchIndex    = 0;
  size_t wildcardIndex = std::string::npos;

  while (strIndex < strLen) {
    if (patternIndex < patternLen && (pattern[patternIndex] == str[strIndex] || pattern[patternIndex] == '_')) {
      patternIndex++;
      strIndex++;
    } else if (patternIndex < patternLen && pattern[patternIndex] == '%') {
      wildcardIndex = patternIndex;
      matchIndex    = strIndex;
      patternIndex++;
    } else if (wildcardIndex != std::string::npos) {
      patternIndex = wildcardIndex + 1;
      matchIndex++;
      strIndex = matchIndex;
    } else {
      return false;
    }
  }

  while (patternIndex < patternLen && pattern[patternIndex] == '%') {
    patternIndex++;
  }

  return patternIndex == patternLen;
}

RC Value::to_regex(std::string regex) const
{
  regex                           = extractCharacters(regex);
  AttrType *att                   = (AttrType *)(&(this->attr_type_));
  *att                            = LIKE_REGEX;
  *(std::string *)(&(str_value_)) = regex;
  return RC::SUCCESS;
}
