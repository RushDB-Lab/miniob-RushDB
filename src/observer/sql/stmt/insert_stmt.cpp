/* Copyright (c) 2021OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Wangyunlai on 2022/5/22.
//

#include "sql/stmt/insert_stmt.h"
#include "common/log/log.h"
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/table/table.h"
#include <string>
#include <vector>

InsertStmt::InsertStmt(Table *table, std::vector<std::vector<Value>> values, int value_amount, int num)
    : table_(table), values_(values), value_amount_(value_amount), values_num_(num)
{}

std::vector<std::vector<Value>> convertToGroups(const std::vector<Value> &input, int num)
{
  std::vector<std::vector<Value>> output;

  int size      = input.size();
  int numGroups = (size + num - 1) / num;  // 向上取整，计算分组数

  for (int i = 0; i < numGroups; i++) {
    std::vector<Value> group;
    int                start = i * num;
    int                end   = std::min(start + num, size);  // 最后一组可能不足 num 个元素

    for (int j = start; j < end; j++) {
      group.push_back(input[j]);
    }

    output.push_back(group);
  }

  return output;
}

RC InsertStmt::create(Db *db, const InsertSqlNode &inserts, Stmt *&stmt)
{
  RC          rc         = RC::SUCCESS;
  const char *table_name = inserts.relation_name.c_str();
  if (nullptr == db || nullptr == table_name || inserts.values.empty()) {
    LOG_WARN("invalid argument. db=%p, table_name=%p, value_num=%d",
        db, table_name, static_cast<int>(inserts.values.size()));
    return RC::INVALID_ARGUMENT;
  }

  // check whether the table exists
  Table *table = db->find_table(table_name);
  if (nullptr == table) {
    LOG_WARN("no such table. db=%s, table_name=%s", db->name(), table_name);
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }

  int              counts     = inserts.values.size();
  const TableMeta &table_meta = table->table_meta();
  const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
  if (counts % field_num != 0)
    return RC::FAILURE;
  std::vector<std::vector<Value>> group_values = convertToGroups(inserts.values, field_num);

  for (int index = 0; index < group_values.size(); index++) {
    // check the fields number
    const Value     *values     = group_values[index].data();
    const int        value_num  = static_cast<int>(group_values[index].size());
    const TableMeta &table_meta = table->table_meta();
    const int        field_num  = table_meta.field_num() - table_meta.sys_field_num();
    if (field_num != value_num) {
      LOG_WARN("schema mismatch. value num=%d, field num in schema=%d", value_num, field_num);
      return RC::SCHEMA_FIELD_MISSING;
    }
//
    // check fields type
    const int sys_field_num = table_meta.sys_field_num();
    for (int i = 0; i < value_num; i++) {
      const FieldMeta *field_meta = table_meta.field(i + sys_field_num);
      const AttrType   field_type = field_meta->type();
      const AttrType   value_type = values[i].attr_type();
      if (field_type != value_type) {  // TODO try to convert the value type to field type
        rc = type_convert(value_type, field_type, values[i], field_meta->nullable());
        if (rc != RC::SUCCESS) {
          LOG_WARN("field type mismatch. table=%s, field=%s, field type=%d, value_type=%d",
          table_name, field_meta->name(), field_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        }
      }
    }
  }
  // everything alright
  stmt = new InsertStmt(table, group_values, group_values[0].size(), group_values.size());
  table->add_rownum(group_values.size());
  return RC::SUCCESS;
}
/*注释：这个函数的作用是将插入的数据转换成对应的数据类型，比如插入的数据是char类型，但是表中的数据是int类型，那么就要将char类型转换成int类型
 * 例如：表中的数据是int类型，但是插入的数据是char类型，那么就要将char类型转换成int类型
*/

RC InsertStmt::type_convert(AttrType value_type, AttrType file_type, const Value &value, bool nullable)
{
  RC rc = RC::SUCCESS;
  switch (value_type) {

    case null: {
      // is nullable?
      if (nullable)
        return RC::SUCCESS;
      return RC::FAILURE;
    }
    case CHARS: {
      // char -> date
      if (file_type == DATES && Value::is_date(value.get_string().c_str())) {
        int flag = value.char_to_int32();
        if (!flag) {
          LOG_WARN("Date type mismatch. field type=%d, value_type=%d",
          file_type, value_type);
          return RC::SCHEMA_FIELD_TYPE_MISMATCH;
        } else
          return RC::SUCCESS;
      }
      // char -> INT
      else if (file_type == INTS) {
        std::string num_str = extractDigits_int(value.get_string());
        rc                  = value.char_to_int(num_str);
      }
      // char -> FLOAT
      else if (file_type == FLOATS) {
        std::string float_num = extractDigits_float(value.get_string());
        rc                    = value.char_to_float(float_num);
      }
      // 都不是那就失败
      else
        rc = RC::TPRE_CONVERT_FAILURE;
    } break;
    case INTS: {
      // int -> char
      if (file_type == CHARS) {
        rc = value.num_to_char();
      }
      // int -> float
      else if (file_type == FLOATS) {
        rc = value.int_to_float();
      } else
        rc = RC::TPRE_CONVERT_FAILURE;

    } break;
    case FLOATS: {
      // float ->char
      if (file_type == CHARS) {
        rc = value.float_to_char();
      } else if (file_type == INTS) {
        rc = value.float_to_int();
      } else
        rc = RC::TPRE_CONVERT_FAILURE;
    }
  }

  return rc;
}

std::string InsertStmt::extractDigits_int(const std::string &str)
{
  std::string digits;

  // 遍历字符串中的字符
  for (char c : str) {
    if (std::isdigit(c)) {
      digits += c;  // 如果是数字，将其添加到结果字符串中
    } else {
      break;  // 如果遇到非数字字符，跳出循环
    }
  }

  return digits;
}

std::string InsertStmt::extractDigits_float(const std::string &str)
{
  std::string number;
  size_t      i          = 0;
  bool        hasDecimal = false;

  while (i < str.length() && (std::isdigit(str[i]) || str[i] == '.')) {
    if (str[i] == '.') {
      if (hasDecimal) {
        // 已经有小数点了，提取结束
        break;
      }
      hasDecimal = true;
    }
    number += str[i];
    i++;
  }

  return number;
}

/*3 | 1A | 10.5
ID | NAME | AGE
SELECT * FROM Typecast_table_1 WHERE name>=1;
-3 | 1A | 10.5
ID | NAME | AGE
SELECT * FROM Typecast_table_1 WHERE name<>'a' and name <>'b';
0 | C | 0*/