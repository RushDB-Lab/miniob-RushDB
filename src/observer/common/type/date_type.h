/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/11                                    *
 * @Description : DateType header file                         *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "common/type/data_type.h"

/**
 * @brief 日期类型
 * @ingroup DateType
 */
class DateType : public DataType
{
public:
  DateType() : DataType(AttrType::DATES) {}
  ~DateType() override = default;

  // 是否需要考虑日期与其它类型的转换？（不需要）
  // 不用实现 cast to，也不需要考虑其他类型转 date
  int cast_cost(AttrType type) override;
  int compare(const Value &left, const Value &right) const override;
  RC  to_string(const Value &val, string &result) const override;
};
