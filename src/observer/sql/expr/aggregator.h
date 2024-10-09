/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http:
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "common/value.h"
#include "common/rc.h"

class Aggregator
{
public:
  virtual ~Aggregator() = default;

  virtual RC accumulate(const Value &value) = 0;
  virtual RC evaluate(Value &result)        = 0;

protected:
  Value value_ = Value(NullValue());
};

class CountAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      return RC::SUCCESS;
    }
    count_++;
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    result = Value(count_);
    return RC::SUCCESS;
  }

private:
  int count_ = 0;
};

class AvgAggregator : public Aggregator
{
public:
  RC accumulate(const Value &value) override
  {
    if (value.is_null()) {
      return RC::SUCCESS;
    }
    if (value_.is_null()) {
      value_ = value;
      count_ = 1;
    } else {
      Value::add(value, value_, value_);
      count_++;
    }
    return RC::SUCCESS;
  }

  RC evaluate(Value &result) override
  {
    if (count_ > 0) {
      Value avg = value_;
      avg       = Value(avg.get_float() / static_cast<float>(count_));
      result    = avg;
    } else {
      result = Value(NullValue());
    }
    return RC::SUCCESS;
  }

private:
  int count_ = 0;
};

#define _agg(FUN)                            \
public:                                      \
  RC accumulate(const Value &value) override \
  {                                          \
    if (value.is_null()) {                   \
      return RC::SUCCESS;                    \
    }                                        \
    if (value_.is_null()) {                  \
      value_ = value;                        \
    } else {                                 \
      FUN;                                   \
    }                                        \
    return RC::SUCCESS;                      \
  }                                          \
  RC evaluate(Value &result) override        \
  {                                          \
    result = value_;                         \
    return RC::SUCCESS;                      \
  }

class SumAggregator : public Aggregator
{
  _agg(Value::add(value, value_, value_))
};

class MaxAggregator : public Aggregator
{
  _agg(if (value.compare(value_) > 0) { value_ = value; })
};

class MinAggregator : public Aggregator
{
  _agg(if (value.compare(value_) < 0) { value_ = value; })
};
