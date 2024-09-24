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
// Created by Wangyunlai on 2022/5/22.
//

#include "common/rc.h"
#include "common/log/log.h"
#include "common/lang/string.h"
#include "sql/parser/value.h"
#include "sql/stmt/filter_stmt.h"
#include "storage/db/db.h"
#include "storage/table/table.h"

FilterStmt::~FilterStmt()
{
  for (FilterUnit *unit : filter_units_) {
    delete unit;
  }
  filter_units_.clear();
}

RC FilterStmt::create(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode *conditions, int condition_num, FilterStmt *&stmt, bool is_like)
{
  RC rc                = RC::SUCCESS;
  stmt                 = nullptr;
  FilterStmt *tmp_stmt = new FilterStmt();
  if (is_like) {
    std::string att_name = conditions->att_name;
    for (int i = 0; i < condition_num; i++) {
      if (conditions[i].is_like == true && conditions[i].is_not_like == false) {
        conditions[i].left_value.to_regex(conditions[i].like);
      } else if (conditions[i].is_like == false && conditions[i].is_not_like == true) {
        conditions[i].left_value.to_regex(conditions[i].not_like);
      } else if (!(conditions[i].is_like ^ conditions[i].is_not_like)) {
        return RC::FAILURE;
      }

      FilterUnit *filter_unit = nullptr;
      rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
      if (rc != RC::SUCCESS) {
        delete tmp_stmt;
        LOG_WARN("failed to create filter unit. condition index=%d", i);
        return rc;
      }
      tmp_stmt->filter_units_.push_back(filter_unit);
    }
  }

  else {
    for (int i = 0; i < condition_num; i++) {
      if (default_table != nullptr)
        cheak_type(conditions, default_table, tables, db);
      FilterUnit *filter_unit = nullptr;
      rc                      = create_filter_unit(db, default_table, tables, conditions[i], filter_unit);
      if (rc != RC::SUCCESS) {
        delete tmp_stmt;
        LOG_WARN("failed to create filter unit. condition index=%d", i);
        return rc;
      }
      tmp_stmt->filter_units_.push_back(filter_unit);
    }
  }

  // 建立子查询
  for (int i = 0; i < condition_num; i++) {
    if (conditions[i].sub_select != nullptr) {
      SelectStmt *child_select_stmt = nullptr;
      Stmt       *stmt_ptr          = nullptr;  // debug用的
      rc                            = SelectStmt::create(db, *conditions[i].sub_select, stmt_ptr);
      child_select_stmt             = static_cast<SelectStmt *>(stmt_ptr);
      if (rc != RC::SUCCESS || child_select_stmt == nullptr) {
        LOG_WARN("failed to create child select stmt");
        return rc;
      }

      tmp_stmt->child_select_stmt_.push_back(child_select_stmt);
    }
  }

  stmt = tmp_stmt;

  return rc;
}

RC get_table_and_field_with_attname(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field, std::string attr_name)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  field = table->table_meta().field(attr_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC get_table_and_field(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const RelAttrSqlNode &attr, Table *&table, const FieldMeta *&field)
{
  if (common::is_blank(attr.relation_name.c_str())) {
    table = default_table;
  } else if (nullptr != tables) {
    auto iter = tables->find(attr.relation_name);
    if (iter != tables->end()) {
      table = iter->second;
    }
  } else {
    table = db->find_table(attr.relation_name.c_str());
  }
  if (nullptr == table) {
    LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
    return RC::SCHEMA_TABLE_NOT_EXIST;
  }
  field = table->table_meta().field(attr.attribute_name.c_str());
  if (nullptr == field) {
    LOG_WARN("no such field in table: table %s, field %s", table->name(), attr.attribute_name.c_str());
    table = nullptr;
    return RC::SCHEMA_FIELD_NOT_EXIST;
  }

  return RC::SUCCESS;
}

RC FilterStmt::create_child_select(Db *db, const ConditionSqlNode *conditions, SelectStmt *&stmt)
{
  if (conditions->sub_select != nullptr) {
    Stmt *child_select_stmt = nullptr;
    RC    rc                = SelectStmt::create(db, *conditions->sub_select, child_select_stmt);
    if (rc != RC::SUCCESS) {
      LOG_WARN("failed to create child select stmt");
      return rc;
    }
    stmt = static_cast<SelectStmt *>(child_select_stmt);
  }
  return RC::SUCCESS;
}
RC FilterStmt::create_filter_unit(Db *db, Table *default_table, std::unordered_map<std::string, Table *> *tables,
    const ConditionSqlNode &condition, FilterUnit *&filter_unit, int num)
{
  RC rc = RC::SUCCESS;
  if (condition.is_like || condition.is_not_like) {
    filter_unit            = new FilterUnit;
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field_with_attname(
        db, default_table, tables, condition.left_attr, table, field, condition.att_name);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
    if (condition.is_like)
      filter_unit->set_comp(EQUAL_TO);
    else if (condition.is_not_like)
      filter_unit->set_comp(NOT_EQUAL);
    // FIELD LIKE VALUE
    FilterObj filter_obj_right;
    filter_obj_right.init_value(condition.left_value);
    filter_unit->set_right(filter_obj_right);

    return rc;
  }
  CompOp comp = condition.comp;
  if (comp < EQUAL_TO || comp >= NO_OP) {
    LOG_WARN("invalid compare operator : %d", comp);
    return RC::INVALID_ARGUMENT;
  }
  // 检查condition字段是否是date的伪char
  if (condition.right_is_attr == 0 && condition.right_value.attr_type() == CHARS &&
      Value::is_date(condition.right_value.get_string().c_str())) {
    if (condition.right_value.char_to_int32() == 0) {
      LOG_WARN("invalid date  : %s", condition.right_value.get_string().c_str());
      return RC::INVALID_ARGUMENT;
    }
  }
  if (condition.left_is_attr == 0 && condition.left_value.attr_type() == CHARS &&
      Value::is_date(condition.left_value.get_string().c_str())) {
    if (condition.left_value.char_to_int32() == 0) {
      LOG_WARN("invalid date  : %s", condition.left_value.get_string().c_str());
      return RC::INVALID_ARGUMENT;
    }
  }

  filter_unit = new FilterUnit;

  if (condition.left_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.left_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_left(filter_obj);
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.left_value);
    filter_unit->set_left(filter_obj);
  }

  if (condition.right_is_attr) {
    Table           *table = nullptr;
    const FieldMeta *field = nullptr;
    rc                     = get_table_and_field(db, default_table, tables, condition.right_attr, table, field);
    if (rc != RC::SUCCESS) {
      LOG_WARN("cannot find attr");
      return rc;
    }
    FilterObj filter_obj;
    filter_obj.init_attr(Field(table, field));
    filter_unit->set_right(filter_obj);
  } else {
    FilterObj filter_obj;
    filter_obj.init_value(condition.right_value);
    filter_unit->set_right(filter_obj);
  }
  filter_unit->set_comp(comp);

  // 检查两个类型是否能够比较
  return rc;
}

std::string extractDigits_int(const std::string &str)
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

std::string extractDigits_float(const std::string &str)
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
AttrType find_att(std::string name, Table *default_table) { return default_table->find_attry_by_name(name); }

RC FilterStmt::cheak_type(
    const ConditionSqlNode *conditions, Table *default_table, std::unordered_map<std::string, Table *> *tables, Db *db)
{

  RC rc = RC::SUCCESS;
  // 确定了左边是属性
  if (conditions->left_is_attr && !conditions->right_is_attr) {
    const RelAttrSqlNode attr = conditions->left_attr;
    if (common::is_blank(attr.relation_name.c_str())) {
      default_table = default_table;
    } else if (nullptr != tables) {
      auto iter = tables->find(attr.relation_name);
      if (iter != tables->end()) {
        default_table = iter->second;
      }
    } else {
      default_table = db->find_table(attr.relation_name.c_str());
    }
    if (nullptr == default_table) {
      LOG_WARN("No such table: attr.relation_name: %s", attr.relation_name.c_str());
      return RC::SCHEMA_TABLE_NOT_EXIST;
    }

    AttrType left_att  = find_att(conditions->left_attr.attribute_name, default_table);
    AttrType right_att = conditions->right_value.attr_type();
    if (left_att == right_att)
      return RC::SUCCESS;
    else if (left_att == DATES && right_att == CHARS && Value::is_date(conditions->right_value.get_string().c_str())) {
      int flag = conditions->right_value.char_to_int32();
      if (!flag) {
        LOG_WARN("Date type mismatch. field type=%d, value_type=%d",
          left_att, right_att);
        return RC::TPRE_CONVERT_FAILURE;
      } else
        return RC::SUCCESS;
    } else if ((left_att == FLOATS || left_att == INTS) && right_att == CHARS) {
      std::string float_num = extractDigits_float(conditions->right_value.get_string());
      rc                    = conditions->right_value.char_to_float(float_num);
    }
  } else if (!conditions->left_is_attr && conditions->right_is_attr) {
    const RelAttrSqlNode attr      = conditions->right_attr;
    AttrType             right_att = find_att(conditions->right_attr.attribute_name, default_table);
    AttrType             left_att  = conditions->left_value.attr_type();
    if (left_att == right_att)
      return RC::SUCCESS;
    else if (right_att == DATES && left_att == CHARS && Value::is_date(conditions->left_value.get_string().c_str())) {
      int flag = conditions->left_value.char_to_int32();
      if (!flag) {
        LOG_WARN("Date type mismatch. field type=%d, value_type=%d",
          right_att, left_att);
        return RC::TPRE_CONVERT_FAILURE;
      } else
        return RC::SUCCESS;
    } else if (right_att == INTS && left_att == CHARS) {
      std::string num_str = extractDigits_int(conditions->left_value.get_string());
      rc                  = conditions->left_value.char_to_int(num_str);
    } else if (right_att == FLOATS && left_att == CHARS) {
      std::string float_num = extractDigits_float(conditions->left_value.get_string());
      rc                    = conditions->left_value.char_to_float(float_num);
    }
  }
  return rc;
}