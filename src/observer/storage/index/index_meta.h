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
// Created by Wangyunlai on 2021/5/12.
//

#pragma once

#include "common/rc.h"
#include "common/lang/string.h"
#include "storage/field/field_meta.h"

#include <json/value.h>

class TableMeta;
class FieldMeta;

namespace Json {
class Value;
}  // namespace Json

/**
 * @brief 描述一个索引
 * @ingroup Index
 * @details 一个索引包含了表的哪些字段，索引的名称等。
 * 如果以后实现了多种类型的索引，还需要记录索引的类型，对应类型的一些元数据等
 */
class IndexMeta
{
public:
  IndexMeta() = default;

  [[nodiscard]] RC init(const char *name, IndexType index_type, const vector<FieldMeta> &fields, bool unique = false);

  void desc(ostream &os) const { os << to_string(); }

  [[nodiscard]] string to_string() const;

  void to_json(Json::Value &json_value) const;

  static RC from_json(const Json::Value &json_value, IndexMeta &index);

  [[nodiscard]] char *make_entry_from_record(const char *record)
  {
    char *entry = new char[fields_total_len_];
    make_entry_from_record(entry, record);
    return entry;
  }

  void make_entry_from_record(char *entry, const char *record)
  {
    for (size_t i = 0; i < fields_.size(); i++) {
      auto &field = fields_[i];
      memcpy(entry + fields_offset_[i], record + field.offset(), field.len());
    }
  }

  [[nodiscard]] const char              *name() const { return name_.c_str(); }
  IndexType                              index_type() const { return index_type_; }
  [[nodiscard]] int                      fields_total_len() const { return fields_total_len_; }
  [[nodiscard]] const vector<FieldMeta> &fields() const { return fields_; }
  [[nodiscard]] bool                     unique() const { return unique_; }
  [[nodiscard]] const vector<int>       &fields_offset() const { return fields_offset_; }

private:
  string            name_;
  IndexType         index_type_;
  int               fields_total_len_ = 0;
  vector<int>       fields_offset_;
  vector<FieldMeta> fields_;
  bool              unique_;
};
