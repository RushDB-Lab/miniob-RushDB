/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/20                                    *
 * @Description : UpdateLogicalOperator header file            *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "sql/operator/logical_operator.h"

/**
 * @brief 逻辑算子，用于执行udpate语句
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  explicit UpdateLogicalOperator(Table *table, const char *attribute_name, const Value *value);
  ~UpdateLogicalOperator() override = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }
  Table              *table() const { return table_; }
  const char         *attribute_name() const { return attribute_name_; }
  const Value        *values() const { return value_; }

private:
  Table       *table_          = nullptr;
  const char  *attribute_name_ = nullptr;
  const Value *value_          = nullptr;
};
