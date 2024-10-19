/***************************************************************
 *                                                             *
 * @Author      : Koschei                                      *
 * @Email       : nitianzero@gmail.com                         *
 * @Date        : 2024/10/18                                   *
 * @Description : ivfflat index source file                    *
 *                                                             *
 * Copyright (c) 2024 Koschei                                  *
 * All rights reserved.                                        *
 *                                                             *
 ***************************************************************/

#include <random>

#include "storage/index/ivfflat_index.h"

#define MAX_ITERATIONS 5

using Vector = std::vector<float>;

void vector_add(Vector &a, const Vector &b)
{
  for (size_t i = 0; i < a.size(); i++) {
    a[i] += b[i];
  }
}

void vector_scalar_div(Vector &a, float x)
{
  for (auto &y : a) {
    y /= x;
  }
}

// 计算两个向量之间的距离
float compute_distance(const Vector &a, const Vector &b, NormalFunctionType dist_fn)
{
  switch (dist_fn) {
    case NormalFunctionType::L2_DISTANCE: return builtin::l2_distance(a, b);
    case NormalFunctionType::COSINE_DISTANCE: return builtin::cosine_distance(a, b);
    case NormalFunctionType::INNER_PRODUCT: return builtin::inner_product(a, b);
    default: return 0;
  }
}

// 找到离给定向量最近的质心
auto find_centroid(const Vector &vec, const std::vector<Vector> &centroids, NormalFunctionType dist_fn) -> size_t
{
  size_t best_index   = 0;
  float  min_distance = std::numeric_limits<float>::max();
  for (size_t i = 0; i < centroids.size(); i++) {
    float distance = compute_distance(vec, centroids[i], dist_fn);
    if (distance < min_distance) {
      min_distance = distance;
      best_index   = i;
    }
  }
  return best_index;
}

// 根据数据和旧质心计算新质心
auto find_centroids(const std::vector<std::pair<Vector, RID>> &data, const std::vector<Vector> &centroids,
    NormalFunctionType dist_fn) -> std::vector<Vector>
{
  std::vector<Vector> new_centroids(centroids.size(), Vector(centroids[0].size(), 0.0));
  std::vector<size_t> counts(centroids.size(), 0);

  // 聚类点累加
  for (const auto &[vec, rid] : data) {
    size_t index = find_centroid(vec, centroids, dist_fn);
    vector_add(new_centroids[index], vec);
    counts[index]++;
  }

  // 计算平均值作为新质心
  for (size_t i = 0; i < new_centroids.size(); i++) {
    if (counts[i] > 0) {
      vector_scalar_div(new_centroids[i], counts[i]);
    } else {
      new_centroids[i] = centroids[i];  // 无数据点的运行质心
    }
  }
  return new_centroids;
}

RC IvfflatIndex::create(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
{
  if (inited_) {
    LOG_WARN("Failed to create index due to the index has been created before. file_name:%s, index:%s",
        file_name, index_meta.to_string().c_str());
    return RC::RECORD_OPENNED;
  }

  Index::init(index_meta);

  // 暂时先不支持持久化
  // BufferPoolManager &bpm = table->db()->buffer_pool_manager();
  // RC                 rc  = index_handler_.create(table->db()->log_handler(), bpm, file_name, index_meta);
  // if (RC::SUCCESS != rc) {
  //   LOG_WARN("Failed to create index_handler, file_name:%s, index:%s, rc:%s",
  //       file_name, index_meta.to_string().c_str(), strrc(rc));
  //   return rc;
  // }

  inited_     = true;
  table_      = table;
  field_meta_ = field_meta;
  LOG_INFO("Successfully create index, file_name:%s, index:%s",
    file_name, index_meta.to_string().c_str());
  return RC::SUCCESS;
}

RC IvfflatIndex::open(Table *table, const char *file_name, const IndexMeta &index_meta, const FieldMeta &field_meta)
{
  return RC::SUCCESS;
}

RC IvfflatIndex::close() { return RC::SUCCESS; }

RC IvfflatIndex::build_index(
    std::vector<std::pair<Vector, RID>> &initial_data, NormalFunctionType distance_fn, const std::vector<int> &options)
{
  // 初始化距离度量函数
  distance_fn_ = distance_fn;

  // 初始化参数
  lists_  = options[0];
  probes_ = options[1];

  if (initial_data.empty()) {
    return RC::SUCCESS;
  }

  std::mt19937                    gen(std::random_device{}());
  std::uniform_int_distribution<> dis(0, initial_data.size() - 1);

  // 随机选择初始质心
  centroids_.resize(lists_);
  for (auto &centroid : centroids_) {
    centroid = initial_data[dis(gen)].first;
  }

  // 迭代更新质心直到收敛
  size_t cnt     = 0;  // 迭代次数
  bool   changed = true;
  while (changed && cnt < MAX_ITERATIONS) {
    changed            = false;
    auto new_centroids = find_centroids(initial_data, centroids_, distance_fn_);

    // 检查质心是否发生变化
    for (size_t i = 0; i < lists_; i++) {
      if (compute_distance(new_centroids[i], centroids_[i], distance_fn_) > 0.01) {
        changed = true;
      }
      centroids_[i] = std::move(new_centroids[i]);
    }

    ++cnt;
  }

  // 将数据点分配到最近的质心
  centroids_buckets_.resize(lists_);
  for (auto &[vec, rid] : initial_data) {
    size_t index = find_centroid(vec, centroids_, distance_fn_);
    centroids_buckets_[index].emplace_back(std::move(vec), rid);
  }

  return RC::SUCCESS;
}

std::vector<RID> IvfflatIndex::ann_search(const std::vector<float> &base_vector, size_t limit)
{
  std::vector<std::pair<float, size_t>> centroid_distances;

  // 计算与所有簇中心的距离
  for (size_t i = 0; i < centroids_.size(); i++) {
    float dist = compute_distance(base_vector, centroids_[i], distance_fn_);
    centroid_distances.emplace_back(dist, i);
  }

  // 找到最近的 probes_ 个簇
  std::sort(centroid_distances.begin(),
      centroid_distances.end(),
      [&](const std::pair<float, size_t> &a, const std::pair<float, size_t> &b) {
        return a.first < b.first;  // 按距离升序排序
      });

  std::vector<std::pair<float, RID>> candidates;

  // 探测最近的 probes_ 个簇
  for (size_t i = 0; i < probes_; i++) {
    size_t cluster_index = centroid_distances[i].second;
    for (const auto &[vec, rid] : centroids_buckets_[cluster_index]) {
      float dist = compute_distance(base_vector, vec, distance_fn_);
      candidates.emplace_back(dist, rid);
    }
  }

  // 根据距离排序并选取前 limit 个结果
  std::sort(candidates.begin(), candidates.end(), [&](const std::pair<float, RID> &a, const std::pair<float, RID> &b) {
    return a.first < b.first;  // 按距离升序排序
  });

  auto             size = std::min(candidates.size(), limit);
  std::vector<RID> result(size);
  for (size_t i = 0; i < size; i++) {
    result[i] = candidates[i].second;
  }

  return result;
}

Vector IvfflatIndex::get_vector(const char *record)
{
  int    size = field_meta_.len() / sizeof(float);
  Vector vector(size);
  // 直接将记录位置调整为适当的浮点数指针
  const float *data = reinterpret_cast<const float *>(record + field_meta_.offset());
  // 使用标准库函数来进行快速的内存复制
  std::copy(data, data + size, vector.begin());
  return vector;
}

RC IvfflatIndex::insert_entry(const char *record, const RID *rid)
{
  Vector vector = get_vector(record);
  size_t index  = find_centroid(vector, centroids_, this->distance_fn_);
  centroids_buckets_[index].emplace_back(std::move(vector), *rid);
  return RC::SUCCESS;
}

RC IvfflatIndex::delete_entry(const char *record, const RID *rid) { return RC::SUCCESS; }

RC IvfflatIndex::sync() { return RC::SUCCESS; }
