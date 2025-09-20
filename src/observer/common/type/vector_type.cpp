//
// Created by root on 24-10-14.
//

#include "common/type/vector_type.h"

#include "common/value.h"
#include <iomanip>

int VectorType::compare(const Value &left, const Value &right) const
{
  // 获取左向量和右向量的指针
  const float *left_data  = reinterpret_cast<const float *>(left.data());
  const float *right_data = reinterpret_cast<const float *>(right.data());

  // 获取向量的长度
  int left_count  = left.length() / sizeof(float);
  int right_count = right.length() / sizeof(float);

  // 如果向量长度不一致，先比较长度
  if (left_count != right_count) {
    return (left_count < right_count) ? -1 : 1;
  }

  // 逐元素比较两个向量
  for (int i = 0; i < left_count; ++i) {
    if (left_data[i] < right_data[i]) {
      return -1;  // left 小于 right
    } else if (left_data[i] > right_data[i]) {
      return 1;  // left 大于 right
    }
  }

  // 如果每个元素都相等，则两个向量相等
  return 0;
}

RC VectorType::cast_to(const Value &val, AttrType type, Value &result, bool allow_type_promotion) const
{
  if (type == AttrType::CHARS) {
    result = Value(val.to_string().c_str());
    return RC::SUCCESS;
  }
  return RC::INTERNAL;
}
RC  VectorType::set_value_from_str(Value &val, const string &data) const { return RC::UNIMPLEMENTED; }
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
      oss << ",";  // 在每个元素之间加逗号和空格
    }
    oss << common::double_to_str(data[i]);
  }

  oss << "]";  // 关闭数组的方括号

  // 将结果存储到 result 中
  result = oss.str();

  return RC::SUCCESS;
}

RC VectorType::add(const Value &left, const Value &right, Value &result) const
{
  // 获取左向量和右向量的指针
  const float *left_data  = reinterpret_cast<const float *>(left.data());
  const float *right_data = reinterpret_cast<const float *>(right.data());

  // 获取向量的长度
  int left_count  = left.length() / sizeof(float);
  int right_count = right.length() / sizeof(float);

  // 确保两个向量的长度相同
  if (left_count != right_count) {
    return RC::VECTOR_DIM_MISMATCH;  // 长度不匹配，返回错误
  }

  // 创建一个新的结果向量
  float *result_data = new float[left_count];

  // 执行逐元素加法
  for (int i = 0; i < left_count; ++i) {
    result_data[i] = left_data[i] + right_data[i];
  }

  // 将结果存储到 result 中
  result.set_vector(result_data, left.length());

  return RC::SUCCESS;
}

RC VectorType::subtract(const Value &left, const Value &right, Value &result) const
{
  // 获取左向量和右向量的指针
  const float *left_data  = reinterpret_cast<const float *>(left.data());
  const float *right_data = reinterpret_cast<const float *>(right.data());

  // 获取向量的长度
  int left_count  = left.length() / sizeof(float);
  int right_count = right.length() / sizeof(float);

  // 确保两个向量的长度相同
  if (left_count != right_count) {
    return RC::VECTOR_DIM_MISMATCH;  // 长度不匹配，返回错误
  }

  // 创建一个新的结果向量
  float *result_data = new float[left_count];

  // 执行逐元素减法
  for (int i = 0; i < left_count; ++i) {
    result_data[i] = left_data[i] - right_data[i];
  }

  // 将结果存储到 result 中
  result.set_vector(result_data, left.length());

  return RC::SUCCESS;
}

RC VectorType::multiply(const Value &left, const Value &right, Value &result) const
{
  // 获取左向量和右向量的指针
  const float *left_data  = reinterpret_cast<const float *>(left.data());
  const float *right_data = reinterpret_cast<const float *>(right.data());

  // 获取向量的长度
  int left_count  = left.length() / sizeof(float);
  int right_count = right.length() / sizeof(float);

  // 确保两个向量的长度相同
  if (left_count != right_count) {
    return RC::VECTOR_DIM_MISMATCH;  // 长度不匹配，返回错误
  }

  // 创建一个新的结果向量
  float *result_data = new float[left_count];

  // 执行逐元素乘法
  for (int i = 0; i < left_count; ++i) {
    result_data[i] = left_data[i] * right_data[i];
  }

  // 将结果存储到 result 中
  result.set_vector(result_data, left.length());

  return RC::SUCCESS;
}
