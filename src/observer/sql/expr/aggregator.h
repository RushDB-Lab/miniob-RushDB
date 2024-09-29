/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2024/05/29.
//

#pragma once

#include "common/value.h"
#include "common/rc.h"

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;
};

class CountAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    // 只要传入的值类型不为未定义，就增加计数
    if (value.attr_type() != AttrType::UNDEFINED && !value.is_null()) {
      count_++;
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = Value(count_);  // 返回计数结果
    return RC::SUCCESS;
  }

private:
  int count_ = 0;  // 计数器
};

class SumAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = Value(NullValue());
      }
    } else {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = value;
      } else {
        Value::add(value, value_, value_);
      }
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = value_;
    return RC::SUCCESS;
  }

private:
  Value value_;  // 累加的和
};

class AvgAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = Value(NullValue());
      }
    } else {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = value;
        count_ = 1;
      } else {
        Value::add(value, value_, value_);
        count_++;
      }
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    if (value_.is_null()) {
      result = Value(NullValue());
      return RC::SUCCESS;
    }

    if (count_ == 0) {
      result = Value(0);  // 避免除以零
    } else {
      // 计算平均值
      Value avg = value_;
      avg       = Value(avg.get_float() / static_cast<float>(count_));  // 这里假设 value_ 是 float 类型
      result    = avg;
    }
    return RC::SUCCESS;
  }

private:
  Value value_;      // 累加的和
  int   count_ = 0;  // 计数器
};

class MaxAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = Value(NullValue());
      }
    } else {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = value;
      } else {
        // 更新最大值
        if (value.compare(value_) > 0) {
          value_ = value;
        }
      }
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = value_;  // 返回最大值
    return RC::SUCCESS;
  }

private:
  Value value_;  // 最大值
};

class MinAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = Value(NullValue());
      }
    } else {
      if (value_.attr_type() == AttrType::UNDEFINED || value_.attr_type() == AttrType::NULLS) {
        value_ = value;
      } else {
        // 更新最小值
        if (value.compare(value_) < 0) {
          value_ = value;
        }
      }
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = value_;  // 返回最小值
    return RC::SUCCESS;
  }

private:
  Value value_;  // 最小值
};
