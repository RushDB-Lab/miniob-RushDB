//
// Created by root on 24-10-14.
//

#include "common/type/vector_type.h"
int VectorType::compare(const Value &left, const Value &right) const { return DataType::compare(left, right); }
RC  VectorType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  return DataType::cast_to(val, type, result, allow_type_promotion);
}
RC VectorType::set_value_from_str(Value &val, const string &data) const
{
  return DataType::set_value_from_str(val, data);
}
int VectorType::cast_cost(AttrType type) { return DataType::cast_cost(type); }
RC  VectorType::to_string(const Value &val, string &result) const { return DataType::to_string(val, result); }