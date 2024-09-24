/* Copyright (c) 2021 Xie Meiyi(xiemeiyi@hust.edu.cn) and OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

//
// Created by Meiyi & Wangyunlai on 2021/5/12.
//

#pragma once

#include <cstddef>
#include <functional>
#include <string>
#include "sql/parser/value.h"
#include "storage/db/db.h"
#include "storage/field/field_meta.h"
#include "storage/table/table_meta.h"

struct RID;
class Record;
class DiskBufferPool;
class RecordFileHandler;
class RecordFileScanner;
class ConditionFilter;
class DefaultConditionFilter;
class Index;
class IndexScanner;
class RecordDeleter;
class Trx;

/**
 * @brief 表
 *
 */
class Table
{
public:
  Table() = default;
  ~Table();

  /**
   * 创建一个表
   * @param path 元数据保存的文件(完整路径)
   * @param name 表名
   * @param base_dir 表数据存放的路径
   * @param attribute_count 字段个数
   * @param attributes 字段
   */
  RC create(int32_t table_id, const char *path, const char *name, const char *base_dir, int attribute_count,
      const AttrInfoSqlNode attributes[]);

  /**
   * 打开一个表
   * @param meta_file 保存表元数据的文件完整路径
   * @param base_dir 表所在的文件夹，表记录数据文件、索引数据文件存放位置
   */
  RC open(const char *meta_file, const char *base_dir);

  /**
   * @brief 根据给定的字段生成一个记录/行
   * @details 通常是由用户传过来的字段，按照schema信息组装成一个record。
   * @param value_num 字段的个数
   * @param values    每个字段的值
   * @param record    生成的记录数据
   */
  RC make_record(int value_num, const Value *values, Record &record);

  /**
   * @brief 在当前的表中插入一条记录
   * @details 在表文件和索引中插入关联数据。这里只管在表中插入数据，不关心事务相关操作。
   * @param record[in/out] 传入的数据包含具体的数据，插入成功会通过此字段返回RID
   */
  RC insert_record(Record &record);
  RC delete_record(const Record &record);
  RC update_record(const Record &record, const char *data, std::string att_name);
  RC visit_record(const RID &rid, bool readonly, std::function<void(Record &)> visitor);
  RC get_record(const RID &rid, Record &record);

  RC recover_insert_record(Record &record);

  // TODO refactor
  RC create_index(Trx *trx, const FieldMeta *field_meta, const char *index_name, bool unique_index_);

  RC get_record_scanner(RecordFileScanner &scanner, Trx *trx, bool readonly);

  RecordFileHandler *record_handler() const { return record_handler_; }

public:
  int32_t         table_id() const { return table_meta_.table_id(); }
  const char     *name() const;
  std::string     get_dir() { return base_dir_; }
  std::string     get_path() { return base_path_; }
  DiskBufferPool *get_data_buffer_pool_() { return data_buffer_pool_; }

  const TableMeta &table_meta() const;

  RC sync();

private:
  RC insert_entry_of_indexes(const char *record, const RID &rid);
  RC delete_entry_of_indexes(const char *record, const RID &rid, bool error_on_not_exists);

private:
  RC init_record_handler(const char *base_dir);

public:
  const FieldMeta     *find_fieldmate_by_name(const char *name);
  int                  find_offset(std::string att_name);
  int                  find_attry_name(std::string att_name);
  AttrType             find_attry_by_name(std::string name);
  Index               *find_index(const char *index_name) const;
  int                  find_att_len(std::string att_name);
  Index               *find_index_by_field(const char *field_name) const;
  std::vector<Index *> indexes() { return indexes_; }
  int                  fiele_size() { return table_meta_.fiele_size(); }
  RC                   destroy_index();
  RC                   SavetoFile();
  RC                   LoadtoFile();
  void                 add_rownum(int num) { row_num += num; }

  friend class Db;

private:
  std::string              base_path_;
  std::string              base_dir_;
  TableMeta                table_meta_;
  DiskBufferPool          *data_buffer_pool_ = nullptr;  /// 数据文件关联的buffer pool
  RecordFileHandler       *record_handler_   = nullptr;  /// 管理整个文件中记录的增删改查
  std::vector<Index *>     indexes_;
  std::vector<std::string> index_field_dir;
  size_t                   row_num = 0;  // 数据一共有多少行
};
