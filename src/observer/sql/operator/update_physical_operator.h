/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/9/17                                    *
 * @Description : UpdatePhysicalOperator header file           *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#pragma once

#include "sql/operator/physical_operator.h"

class Trx;
class UpdateStmt;

/**
 * @brief 物理算子，更新
 * @ingroup PhysicalOperator
 */
class UpdatePhysicalOperator : public PhysicalOperator
{
public:
  UpdatePhysicalOperator(Table *table, std::vector<FieldMeta> field_metas, std::vector<Value> values)
      : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values))
  {}

  ~UpdatePhysicalOperator() override = default;

  PhysicalOperatorType          type() const override { return PhysicalOperatorType::UPDATE; }
  const std::vector<FieldMeta> &field_metas() const { return field_metas_; }
  const std::vector<Value>     &values() const { return values_; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  Trx                   *trx_   = nullptr;
  Table                 *table_ = nullptr;
  std::vector<FieldMeta> field_metas_;
  std::vector<Value>     values_;
  std::vector<Record> records_;
};
