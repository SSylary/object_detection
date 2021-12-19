/**
 * @file dbscan_cluster.h
 * @author SSylary.xzc@gmail.com
 * @brief
 *  This is a simple implement for DBSCAN cluster with C++
 * @version 1.0
 * @date 2021-12-18
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "dbscan_cluster.h"

DBSCANCluster::DBSCANCluster(const uint32_t min_elements, const float epsilon,
                             const std::vector<Point2D> &elements)
    : min_required_size_(min_elements),
      epsilon_(epsilon),
      all_data_(elements) {}

void DBSCANCluster::Process() {
  // -1 for NOISE
  // 0 for UNCLASSIFIED
  // 1 for the largest class
  // 2 for the second largest clss

  if (all_data_.empty()) {
    return;
  }
  uint32_t size = all_data_.size();
  index_label_list_.reserve(size);

  int32_t cluster_id = 1;
  for (int32_t i = 0; i < size; ++i) {
    if (index_label_list_[i] == 0) {
      if (ExpandCluster(all_data_[i], cluster_id)) {
        cluster_id++;
      }
    }
  }
  MakeClusterResultTable();
}

void DBSCANCluster::CalculateCluster(const Point2D &point,
                                     std::vector<int32_t> *const seed_cluster) {
  if (seed_cluster == nullptr) {
    return;
  }
  for (int32_t i = 0; i < all_data_.size(); ++i) {
    if (point.DistanceTo(all_data_[i]) <= epsilon_) {
      seed_cluster->emplace_back(i);
    }
  }
}

bool DBSCANCluster::ExpandCluster(const Point2D &point,
                                  const int32_t cluster_id) {
  std::vector<int32_t> seed_cluster;
  CalculateCluster(point, &seed_cluster);

  if (seed_cluster.size() < min_required_size_) {
    for (auto iter = seed_cluster.begin(); iter != seed_cluster.end(); ++iter) {
      index_label_list_[*iter] = -1;
    }
    return false;
  } else {
    for (uint32_t i = 0; i < seed_cluster.size(); ++i) {
      std::vector<int32_t> sub_seed_cluster;
      CalculateCluster(all_data_[seed_cluster[i]], &sub_seed_cluster);
      if (sub_seed_cluster.size() >= min_required_size_) {
        for (auto sub_iter = sub_seed_cluster.begin();
             sub_iter != sub_seed_cluster.end(); ++sub_iter) {
          if (index_label_list_[*sub_iter] == 0 ||
              index_label_list_[*sub_iter] == -1) {
            if (index_label_list_[*sub_iter] == 0) {
              seed_cluster.emplace_back(*sub_iter);
            }
            index_label_list_[*sub_iter] = cluster_id;
          }
        }
      }
    }
  }
  return true;
}

void DBSCANCluster::MakeClusterResultTable() {
  std::unordered_map<int32_t, std::vector<Point2D>> sort_result_helper;
  for (uint32_t i = 0; i < index_label_list_.size(); ++i) {
    sort_result_helper[index_label_list_[i]].emplace_back(all_data_[i]);
  }

  std::vector<std::pair<int32_t, uint32_t>> id_size_list;
  for (auto iter = sort_result_helper.begin(); iter != sort_result_helper.end();
       ++iter) {
    id_size_list.emplace_back(std::make_pair(iter->first, iter->second.size()));
  }

  std::sort(id_size_list.begin(), id_size_list.end(),
            [&](const std::pair<int32_t, uint32_t> &p1,
                const std::pair<int32_t, uint32_t> &p2) {
              return p1.second > p2.second;
            });

  int32_t index = 1;
  for (auto iter = id_size_list.begin(); iter != id_size_list.end(); ++iter) {
    if (iter->first == -1) {
      cluster_result_[-1] = sort_result_helper[-1];
      continue;
    }
    cluster_result_[index++] = sort_result_helper[iter->first];
  }
}