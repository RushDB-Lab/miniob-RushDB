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
// Created by wangyunlai on 2021/6/11.
//

#include <cstdint>
#include <string.h>
#include <algorithm>
#include <string>
#include "common/defs.h"

namespace common {

int compare_int(void *arg1, void *arg2)
{
  int v1 = *(int *)arg1;
  int v2 = *(int *)arg2;
  return v1 - v2;
}

int compare_date(void *arg1, void *arg2) { return memcmp(arg1, arg2, sizeof(int32_t)); }

int compare_float(void *arg1, void *arg2)
{
  float v1  = *(float *)arg1;
  float v2  = *(float *)arg2;
  float cmp = v1 - v2;
  if (cmp > EPSILON) {
    return 1;
  }
  if (cmp < -EPSILON) {
    return -1;
  }
  return 0;
}

int compare_string(void *arg1, int arg1_max_length, void *arg2, int arg2_max_length)
{
  // const char *s1     = (const char *)arg1;
  // const char *s2     = (const char *)arg2;
  // int         maxlen = std::min(arg1_max_length, arg2_max_length);
  // int         result = strncmp(s1, s2, maxlen);
  // if (0 != result) {
  //   return result;
  // }

  // if (arg1_max_length > maxlen) {
  //   return s1[maxlen] - 0;
  // }

  // if (arg2_max_length > maxlen) {
  //   return 0 - s2[maxlen];
  // }
  // return 0;

  std::string str1((char *)arg1);
  std::string str2((char *)arg2);

  int result = str1.compare(str2);
  if (result == 0) {
    return 0;
  } else if (result < 0) {
    return -1;
  } else {
    return 1;
  }
}
bool isNumeric(const char *str)
{
  if (str == nullptr)
    return false;

  while (*str) {
    if (!isdigit(*str))
      return false;
    str++;
  }

  return true;
}
int getNumericValue(const char *str)
{
  if (str == nullptr)
    return 0;

  char *endPtr;
  int   value = std::strtol(str, &endPtr, 10);

  return value;
}

bool isDecimal(const char *str)
{
  if (str == nullptr)
    return false;

  char  *endPtr;
  double value = std::strtod(str, &endPtr);

  // 判断转换后的结果是否为零，且指针位置是否为字符串结尾
  return (value != 0.0) && (*endPtr == '\0');
}

float getDecimalValue(const char *str)
{
  if (str == nullptr)
    return 0.0f;

  char *endPtr;
  float value = std::strtof(str, &endPtr);

  return value;
}

std::string extractDigits_int(const std::string &str)
{
  std::string digits;

  // 遍历字符串中的字符
  for (char c : str) {
    if (std::isdigit(c)) {
      digits += c;  // 如果是数字，将其添加到结果字符串中
    } else {
      break;  // 如果遇到非数字字符，跳出循环
    }
  }

  return digits;
}

int convertToInt(const std::string &str)
{
  try {
    return std::stoi(str);
  } catch (const std::exception &e) {

    // 返回默认值或采取其他错误处理措施
    return -1;
  }
}

std::string extractDigits_float(const std::string &str)
{
  std::string number;
  size_t      i          = 0;
  bool        hasDecimal = false;

  while (i < str.length() && (std::isdigit(str[i]) || str[i] == '.')) {
    if (str[i] == '.') {
      if (hasDecimal) {
        // 已经有小数点了，提取结束
        break;
      }
      hasDecimal = true;
    }
    number += str[i];
    i++;
  }

  return number;
}

int compare_char_with_num(void *arg1, void *arg2, int num_att)
{
  const char *s1 = (const char *)arg1;
  std::string s1_pro(s1);
  switch (num_att) {
    case 1: {
      if (isNumeric(s1)) {
        int num = getNumericValue(s1);
        return num - *(int *)arg2;
      } else if (extractDigits_int(s1_pro).size() != 0) {
        return (int)convertToInt(extractDigits_int(s1_pro)) - *(int *)arg2;
      } else {
        return 0 - *(int *)arg2;
      }
    }
    case 2: {
      if (isDecimal(s1)) {
        float num = getDecimalValue(s1);
        float cmp = num - *(float *)arg2;
        if (cmp > EPSILON) {
          return 1;
        }
        if (cmp < -EPSILON) {
          return -1;
        }
        return 0;
      } else if (extractDigits_float(s1_pro).size() != 0) {
        float cmp = std::stof(extractDigits_float(s1_pro)) - *(float *)arg2;
        if (cmp > EPSILON) {
          return 1;
        }
        if (cmp < -EPSILON) {
          return -1;
        }
        return 0;
      } else {
        float cmp = 0 - *(float *)arg2;
        if (cmp > EPSILON) {
          return 1;
        }
        if (cmp < -EPSILON) {
          return -1;
        }
        return 0;
      }
    }
    default: return 0;
  }
}

bool matchString(const std::string &pattern, const std::string &str)
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
// 0是char，1是int，2是float
int compare_with_regex(void *pattern, void *str, int num)
{
  const char *s1 = (const char *)pattern;
  std::string s1_pro;
  s1_pro.assign(s1);
  if (num == 0) {
    const char *s2 = (const char *)str;
    std::string s2_pro(s2);
    if (matchString(s1_pro, s2_pro)) {
      return 0;
    }
    return 1;
  } else if (num == 1) {
    const int  *s2     = (const int *)str;
    std::string s2_pro = std::to_string(*s2);
    if (matchString(s1_pro, s2_pro)) {
      return 0;
    }
    return 1;
  } else if (num == 2) {
    const float *s2     = (const float *)str;
    std::string  s2_pro = std::to_string(*s2);
    if (matchString(s1_pro, s2_pro)) {
      return 0;
    }
    return 1;
  }
  return -1;
}

}  // namespace common

/*
3 | 3 | 3
ID | NAME | AGE
SELECT * FROM Typecast_table_3 WHERE id<'1.5a';
-1 | 1 | 1
ID | NAME | AGE
SELECT * FROM Typecast_table_3 WHERE id>='3a';
3 | 3 | 3*/