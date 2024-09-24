#include "sql/operator/update_logical_operator.h"
#include <string>

UpdateLogicalOperator::UpdateLogicalOperator(Table *table, std::vector<std::string> names, std::vector<Value> values)
    : table_(table), update_names(names), values_(values)
{}