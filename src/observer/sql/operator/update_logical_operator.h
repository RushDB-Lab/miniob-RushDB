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
  explicit UpdateLogicalOperator(
      BaseTable *table, std::vector<FieldMeta> field_metas, std::vector<std::unique_ptr<Expression>> values);
  ~UpdateLogicalOperator() override = default;

  LogicalOperatorType                       type() const override { return LogicalOperatorType::UPDATE; }
  BaseTable                                *table() const { return table_; }
  std::vector<FieldMeta>                   &field_metas() { return field_metas_; }
  std::vector<std::unique_ptr<Expression>> &values() { return values_; }

private:
  BaseTable                               *table_ = nullptr;
  std::vector<FieldMeta>                   field_metas_;
  std::vector<std::unique_ptr<Expression>> values_;
};
