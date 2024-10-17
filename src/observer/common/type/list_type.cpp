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
// Created by 胡鑫 on 24-10-17.
//

#include "list_type.h"
#include "cassert"
#include "common/value.h"

RC ListType::to_string(const Value &val, string &result) const
{
  assert(val.attr_type() == AttrType::LISTS);
  auto &list = val.get_list();
  result     = "[";
  auto size  = list.size();
  for (int i = 0; i < size; i++) {
    result += list[i].to_string();
    if (i < size - 1) {
      result += ", ";
    }
  }
  result += "]";
  return RC::SUCCESS;
}
