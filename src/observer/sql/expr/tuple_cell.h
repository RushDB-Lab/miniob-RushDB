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
// Created by WangYunlai on 2022/6/7.
//

#pragma once

#include "storage/field/field_meta.h"
#include <iostream>

class TupleCellSpec final
{
public:
  TupleCellSpec() = default;
  TupleCellSpec(const char *table_name, const char *field_name, const char *alias = nullptr);
  explicit TupleCellSpec(const char *alias);
  explicit TupleCellSpec(const std::string &alias);

  const char *table_name() const { return table_name_.c_str(); }
  const char *field_name() const { return field_name_.c_str(); }
  const char *alias() const { return alias_.c_str(); }

  bool alias_empty() const { return alias_.empty(); }
  bool table_field_empty() const { return table_name_.empty() && field_name_.empty(); }

  bool operator==(const TupleCellSpec &other) const
  {
    return (!alias_empty() && !other.alias_empty() && alias_hash_ == other.alias_hash_ && alias_ == other.alias_) ||
           (!table_field_empty() && !other.table_field_empty() && table_name_hash_ == other.table_name_hash_ &&
               field_name_hash_ == other.field_name_hash_ && table_name_ == other.table_name_ &&
               field_name_ == other.field_name_);
  }

private:
  std::string table_name_;
  std::string field_name_;
  std::string alias_;

  std::size_t table_name_hash_;
  std::size_t field_name_hash_;
  std::size_t alias_hash_;

  void init_hash()
  {
    table_name_hash_ = std::hash<std::string>()(table_name_);
    field_name_hash_ = std::hash<std::string>()(field_name_);
    alias_hash_      = std::hash<std::string>()(alias_);
  }
};
