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

RC IndexMeta::init(const char *name, IndexType index_type, const vector<FieldMeta> &fields, bool unique)
{
  name_             = name;
  index_type_       = index_type;
  fields_total_len_ = 0;
  fields_           = fields;
  unique_           = unique;

  for (auto &field : fields) {
    fields_offset_.emplace_back(fields_total_len_);
    fields_total_len_ += field.len();
  }

  return RC::SUCCESS;
}

string IndexMeta::to_string() const
{
  std::ostringstream oss;
  oss << "Index Name: " << name_ << ", Fields: [";
  for (size_t i = 0; i < fields_.size(); ++i) {
    oss << fields_[i].name();
    if (i < fields_.size() - 1) {
      oss << ", ";
    }
  }
  oss << "], Total Length: " << fields_total_len_;
  return oss.str();
}

void IndexMeta::to_json(Json::Value &json_value) const
{
  json_value["name"]             = name_;
  json_value["index_type"]       = static_cast<int>(index_type_);
  json_value["fields_total_len"] = fields_total_len_;
  json_value["unique"]           = unique_;

  Json::Value fields_json(Json::arrayValue);
  for (const auto &field : fields_) {
    Json::Value field_json;
    field.to_json(field_json);
    fields_json.append(field_json);
  }
  json_value["fields"] = fields_json;

  Json::Value offsets_json(Json::arrayValue);
  for (const auto &offset : fields_offset_) {
    offsets_json.append(offset);
  }
  json_value["fields_offset"] = offsets_json;
}

RC IndexMeta::from_json(const Json::Value &json_value, IndexMeta &index)
{
  if (!json_value.isMember("name") || !json_value.isMember("index_type") || !json_value.isMember("fields") ||
      !json_value.isMember("fields_total_len") || !json_value.isMember("fields_offset")) {
    return RC::INVALID_ARGUMENT;
  }

  index.name_             = json_value["name"].asString();
  index.index_type_       = static_cast<IndexType>(json_value["index_type"].asInt());
  index.fields_total_len_ = json_value["fields_total_len"].asInt();
  index.unique_           = json_value["unique"].asBool();

  const Json::Value &fields_json = json_value["fields"];
  for (const auto &field_json : fields_json) {
    FieldMeta field;
    RC        rc = FieldMeta::from_json(field_json, field);
    if (rc != RC::SUCCESS) {
      return rc;
    }
    index.fields_.push_back(field);
  }

  const Json::Value &offsets_json = json_value["fields_offset"];
  for (const auto &offset : offsets_json) {
    index.fields_offset_.push_back(offset.asInt());
  }

  return RC::SUCCESS;
}
