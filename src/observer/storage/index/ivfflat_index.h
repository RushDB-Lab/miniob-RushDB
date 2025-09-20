/* Copyright (c) 2021 OceanBase and/or its affiliates. All rights reserved.
miniob is licensed under Mulan PSL v2.
You can use this software according to the terms and conditions of the Mulan PSL v2.
You may obtain a copy of Mulan PSL v2 at:
         http://license.coscl.org.cn/MulanPSL2
THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
See the Mulan PSL v2 for more details. */

#pragma once

#include "storage/index/index.h"
#include "sql/builtin/builtin.h"

/**
 * @brief ivfflat 向量索引
 * @ingroup Index
 */
class IvfflatIndex : public Index
{
public:
  using Vector = std::vector<float>;

  IvfflatIndex()                    = default;
  ~IvfflatIndex() noexcept override = default;

  RC create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) override;

  RC open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta) override;

  RC close();

  std::vector<RID> ann_search(const std::vector<float> &base_vector, size_t limit);

  Vector get_vector(const char *record);

  RC insert_entry(const char *record, const RID *rid) override;

  RC delete_entry(const char *record, const RID *rid) override;

  RC sync() override;

  RC build_index(std::vector<std::pair<Vector, RID>> &initial_data, NormalFunctionType distance_fn,
      const std::vector<int> &options);

  NormalFunctionType distance_fn() { return distance_fn_; }

private:
  bool   inited_ = false;
  Table *table_  = nullptr;
  int    lists_  = 1;
  int    probes_ = 1;

  FieldMeta field_meta_;  // 建立索引字段元数据

  // 距离度量函数
  NormalFunctionType distance_fn_;

  // 质心
  std::vector<Vector> centroids_;

  // 每个质心周围的点
  std::vector<std::vector<std::pair<Vector, RID>>> centroids_buckets_;
};
