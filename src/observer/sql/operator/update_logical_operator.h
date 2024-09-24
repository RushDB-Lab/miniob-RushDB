#pragma once

#include <string>
#include <vector>

#include "sql/operator/logical_operator.h"
#include "sql/parser/parse_defs.h"

/**
 * @brief 更新逻辑算子
 * @ingroup LogicalOperator
 */
class UpdateLogicalOperator : public LogicalOperator
{
public:
  UpdateLogicalOperator(Table *table, std::vector<std::string> names, std::vector<Value> values);
  virtual ~UpdateLogicalOperator() = default;

  LogicalOperatorType type() const override { return LogicalOperatorType::UPDATE; }

  Table                    *table() const { return table_; }
  const std::vector<Value> &values() const { return values_; }
  auto                      name() { return update_names; }
  std::vector<Value>       &values() { return values_; }

private:
  Table                   *table_ = nullptr;
  std::vector<Value>       values_;
  std::vector<std::string> update_names;
};