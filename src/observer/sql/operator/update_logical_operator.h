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
  explicit UpdateLogicalOperator(Table *table, std::vector<FieldMeta> field_metas, std::vector<const Value *> values);
  ~        UpdateLogicalOperator() override = default;

  LogicalOperatorType               type() const override { return LogicalOperatorType::UPDATE; }
  Table                            *table() const { return table_; }
  const std::vector<FieldMeta>     &field_metas() const { return field_metas_; }
  const std::vector<const Value *> &values() const { return values_; }

private:
  Table                     *table_ = nullptr;
  std::vector<FieldMeta>     field_metas_;
  std::vector<const Value *>     values_;
};
