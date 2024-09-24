// /* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
// miniob is licensed under Mulan PSL v2.
// You can use this software according to the terms and conditions of the Mulan PSL v2.
// You may obtain a copy of Mulan PSL v2 at:
//          http://license.coscl.org.cn/MulanPSL2
// THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
// EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
// MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
// See the Mulan PSL v2 for more details. */

// //
// // Created by WangYunlai on 2022/6/7.
// //

#pragma once

#include "sql/operator/aggfuncs/basc_agg_func.h"
#include "sql/operator/physical_operator.h"
#include "sql/parser/parse_defs.h"
#include "sql/stmt/select_stmt.h"
#include "storage/field/field.h"
#include "storage/record/record_manager.h"
#include "common/rc.h"
#include <vector>

class Table;

/**
 * @brief 表扫描物理算子
 * @ingroup PhysicalOperator
 */
class AggFuncPhysicalOperator : public PhysicalOperator
{
public:
  AggFuncPhysicalOperator(Table *table, bool readonly, std::vector<Agg_Func> &&agg_func_, std::vector<Field> &&files)
      : table_(table), readonly_(readonly), agg_funcs(agg_func_), fields_(files)
  {}

  virtual ~AggFuncPhysicalOperator() = default;

  std::string param() const override;

  PhysicalOperatorType type() const override { return PhysicalOperatorType::AGG_FUNC; }

  RC   open(Trx *trx) override;
  RC   next() override;
  RC   close() override;
  auto get_agg_func() { return agg_funcs; }
  RC   get_max_tuple(RecordFileScanner &table_scaner, const FieldMeta *field_meta);
  RC   get_min_tuple(RecordFileScanner &table_scaner, const FieldMeta *field_meta);
  RC   get_count_tuple(RecordFileScanner &table_scaner, const FieldMeta *field_meta);
  RC   get_avg_tuple(RecordFileScanner &table_scaner, const FieldMeta *field_meta);
  RC   get_sum_tuple(RecordFileScanner &table_scaner, const FieldMeta *field_meta);
  int  compare_with_record(Record *first, Record *second, const FieldMeta *field_meta);
  RC   make_record(int value_num, const Value *values, Record &record);

  Tuple *current_tuple() override;

  void set_predicates(std::vector<std::unique_ptr<Expression>> &&exprs);

private:
  RC filter(RowTuple &tuple, bool &result);

private:
  Table                                   *table_    = nullptr;
  Trx                                     *trx_      = nullptr;
  bool                                     readonly_ = false;
  RecordFileScanner                        record_scanner_;
  Record                                   current_record_;
  RowTuple                                 tuple_;
  std::vector<std::unique_ptr<Expression>> predicates_;  // TODO chang predicate to table tuple filter
  std::vector<Agg_Func>                    agg_funcs;
  std::vector<Field>                       fields_;
  std::vector<aggregation *>               agg_operators;
};
