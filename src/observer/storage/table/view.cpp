/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/12                                     *
 * @Description : Brief description of the file's purpose      *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include "storage/trx/trx.h"
#include "storage/table/view.h"
#include "storage/common/meta_util.h"

RC View::create(Db *db, int32_t table_id, const char *path, const char *name, const char *base_dir,
    span<const AttrInfoSqlNode> attributes, std::vector<BaseTable *> tables,
    std::unique_ptr<PhysicalOperator> select_oper, StorageFormat storage_format)
{
  if (table_id < 0) {
    LOG_WARN("invalid table id. table_id=%d, table_name=%s", table_id, name);
    return RC::INVALID_ARGUMENT;
  }

  if (common::is_blank(name)) {
    LOG_WARN("Name cannot be empty");
    return RC::INVALID_ARGUMENT;
  }
  LOG_INFO("Begin to create table %s:%s", base_dir, name);

  if (attributes.empty()) {
    LOG_WARN("Invalid arguments. table_name=%s, attribute_count=%d", name, attributes.size());
    return RC::INVALID_ARGUMENT;
  }

  RC rc = RC::SUCCESS;

  // 使用 table_name.table 记录一个表的元数据
  // 判断表文件是否已经存在
  int fd = open(path, O_WRONLY | O_CREAT | O_EXCL | O_CLOEXEC, 0600);
  if (fd < 0) {
    if (EEXIST == errno) {
      LOG_ERROR("Failed to create table file, it has been created. %s, EEXIST, %s", path, strerror(errno));
      return RC::SCHEMA_TABLE_EXIST;
    }
    LOG_ERROR("Create table file failed. filename=%s, errmsg=%d:%s", path, errno, strerror(errno));
    return RC::IOERR_OPEN;
  }

  close(fd);

  // 创建文件
  const vector<FieldMeta> *trx_fields = db->trx_kit().trx_fields();
  if ((rc = table_meta_.init(table_id, name, trx_fields, attributes, storage_format)) != RC::SUCCESS) {
    LOG_ERROR("Failed to init table meta. name:%s, ret:%d", name, rc);
    return rc;  // delete table file
  }

  fstream fs;
  fs.open(path, ios_base::out | ios_base::binary);
  if (!fs.is_open()) {
    LOG_ERROR("Failed to open file for write. file name=%s, errmsg=%s", path, strerror(errno));
    return RC::IOERR_OPEN;
  }

  // 记录元数据到文件中
  table_meta_.serialize(fs);
  fs.close();

  // 只存储视图元数据，不存记录数据
  db_       = db;
  base_dir_ = base_dir;

  tables_ = std::move(tables);

  // 查询物理算子
  select_oper_ = std::move(select_oper);
  // 视图类型
  type_ = TableType::View;

  auto field_metas = *table_meta_.field_metas();
  field_index_.resize(field_metas.size());
  for (int i = 0; i < field_metas.size(); ++i) {
    auto &view_field_meta = field_metas[i];
    bool  find            = false;
    for (auto &table : tables_) {
      auto table_field_meta = table->table_meta().field(view_field_meta.name());
      // 当前视图字段在这个表
      if (table_field_meta != nullptr) {
        field_index_[i] = {table, table_field_meta->field_id()};
        find            = true;
        break;
      }
    }
    if (!find) {
      return RC::SCHEMA_FIELD_MISSING;
    }
  }

  LOG_INFO("Successfully create table %s:%s", base_dir, name);
  return rc;
}

RC View::insert_record(Record &record)
{
  RC rc = RC::SUCCESS;

  for (auto &table : tables_) {
    auto               value_num = table->table_meta().field_num();
    std::vector<Value> values(value_num);

    // 不涉及的字段默认为 null
    for (auto &value : values) {
      value.set_null();
    }

    auto field_metas = *table_meta_.field_metas();
    // 遍历视图的字段找到基表的字段
    for (int i = 0; i < field_metas.size(); ++i) {
      // 基表字段所在索引
      auto [base_table, idx] = field_index_[i];
      // 是一个表则写入 value
      if (strcmp(base_table->name(), table->name()) == 0) {
        // 插入值
        Value value;
        rc = record.get_field(field_metas[i], value);
        if (OB_FAIL(rc)) {
          return rc;
        }
        values[idx] = std::move(value);
      }
    }

    // 生成真正的 record 并插入基表
    Record real_record;
    rc = table->make_record(value_num, values.data(), real_record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to make record. rc=%s", strrc(rc));
      return rc;
    }

    rc = table->insert_record(real_record);
    if (OB_FAIL(rc)) {
      LOG_WARN("failed to insert record into table. rc=%s", strrc(rc));
      return rc;
    }
  }

  return RC::SUCCESS;
}

RC View::delete_record(const Record &record)
{
  RC rc = RC::SUCCESS;
  for (auto &[table, rid] : record.base_rids()) {
    rc = table->delete_record(rid);
    if (OB_FAIL(rc)) {
      return rc;
    }
  }
  return rc;
}

RC View::delete_record(const RID &rid) { return RC::SUCCESS; }

RC View::update_record(const Record &old_record, const Record &new_record) { return RC::SUCCESS; }

RC View::get_record(const RID &rid, Record &record) { return RC::SUCCESS; }

RC View::visit_record(const RID &rid, const function<bool(Record &)> &visitor) { return RC::SUCCESS; }

RC View::sync()
{
  RC rc = RC::SUCCESS;
  // for (Index *index : indexes_) {
  //   rc = index->sync();
  //   if (rc != RC::SUCCESS) {
  //     LOG_ERROR("Failed to flush index's pages. table=%s, index=%s, rc=%d:%s",
  //         name(),
  //         index->index_meta().name(),
  //         rc,
  //         strrc(rc));
  //     return rc;
  //   }
  // }
  //
  // rc = data_buffer_pool_->flush_all_pages();
  // LOG_INFO("Sync table over. table=%s", name());
  return rc;
}

RC View::drop()
{
  auto rc = sync();  // 刷新所有脏页
  if (rc != RC::SUCCESS) {
    return rc;
  }

  auto       table_name = name();
  error_code ec;
  auto       path = table_meta_file(base_dir_.c_str(), table_name);
  if (!filesystem::remove(path, ec)) {
    LOG_ERROR("Drop table meta fail: %s. error=%s", path.c_str(), strerror(errno));
    return RC::IOERR_WRITE;
  }

  return RC::SUCCESS;
}
