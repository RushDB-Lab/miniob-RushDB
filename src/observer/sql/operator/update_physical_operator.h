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
  UpdatePhysicalOperator(
      BaseTable *table, std::vector<FieldMeta> field_metas, std::vector<std::unique_ptr<Expression>> values)
      : table_(table), field_metas_(std::move(field_metas)), values_(std::move(values))
  {}

  ~UpdatePhysicalOperator() override = default;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::UPDATE; }

  RC open(Trx *trx) override;
  RC next() override;
  RC close() override;

  Tuple *current_tuple() override { return nullptr; }

private:
  void rollback();

  Trx                                     *trx_   = nullptr;
  BaseTable                               *table_ = nullptr;
  std::vector<FieldMeta>                   field_metas_;
  std::vector<std::unique_ptr<Expression>> values_;
  std::vector<Record>                      records_;
  vector<pair<Record, Record>>             log_records;
};
