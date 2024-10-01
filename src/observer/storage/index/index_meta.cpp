/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#include "index_meta.h"

RC IndexMeta::init(const char *name, const vector<FieldMeta> &fields)
{
  name_             = name;
  fields_total_len_ = 0;
  fields_           = fields;

  for (auto &field : fields) {
    fields_offset_.emplace_back(fields_total_len_);
    fields_total_len_ += field.len();
  }

  return RC::SUCCESS;
}

string IndexMeta::to_string() const
{
  std::ostringstream oss;
  // TODO
  return oss.str();
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  // TODO
}

RC IndexMeta::from_json(const Json::Value &json_value, IndexMeta &index)
{
  // TODO
  return RC::SUCCESS;
}
