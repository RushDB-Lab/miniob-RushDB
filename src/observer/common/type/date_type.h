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

  int compare(const Value &left, const Value &right) const override;

  RC to_string(const Value &val, string &result) const override;
};
