//
// Created by root on 24-10-14.
//

#include "common/type/vector_type.h"

#include <common/value.h>
int VectorType::compare(const Value &left, const Value &right) const { return DataType::compare(left, right); }
RC  VectorType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  if (type == AttrType::CHARS) {
    result = Value(val.to_string().c_str());
    return RC::SUCCESS;
  }
  return RC::INTERNAL;
}
RC VectorType::set_value_from_str(Value &val, const string &data) const
{
  return DataType::set_value_from_str(val, data);
}
int VectorType::cast_cost(AttrType type) { return DataType::cast_cost(type); }
RC  VectorType::to_string(const Value &val, std::string &result) const
{
  // 获取 float 数组指针
  const auto *data = reinterpret_cast<const float *>(val.data());

  // 计算数组中元素的数量
  int count = val.length() / sizeof(float);

  // 使用字符串流来构建输出字符串
  std::ostringstream oss;
  oss << "[";

  // 遍历数组元素并拼接成字符串
  for (int i = 0; i < count; ++i) {
    if (i != 0) {
      oss << ", ";  // 在每个元素之间加逗号和空格
    }
    oss << data[i];  // 将浮点数输出到字符串流
  }

  oss << "]";  // 关闭数组的方括号

  // 将结果存储到 result 中
  result = oss.str();

  return RC::SUCCESS;
}
