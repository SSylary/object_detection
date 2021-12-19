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

#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

#include "point2d.h"

class DBSCANCluster {
 public:
  explicit DBSCANCluster(const uint32_t min_elements, const float epsilon,
                         const std::vector<Point2D> &elements);
  ~DBSCANCluster() = default;

  void Process();
  void CalculateCluster(const Point2D &point,
                        std::vector<int32_t> *const seed_cluster);
  bool ExpandCluster(const Point2D &Point2D, const int32_t cluster_id);
  void MakeClusterResultTable();

  /*
   std::vector<Element>& get_all_data() const;
   uint32_t get_min_cluster_required_size() const;
   uint32_t get_total_data_size() const;
   float get_epsilon() const;
   */
 private:
  std::unordered_map<int32_t, std::vector<Point2D>> cluster_result_;
  std::vector<int32_t> index_label_list_;
  std::vector<Point2D> all_data_;
  uint32_t min_required_size_;
  float epsilon_;
};