#pragma once

#include <algorithm>

#include "graph.h"

namespace pathfind {

struct QueueNode {
  node_id id;
  int32_t f_score;
};

struct CompareFScore {
  bool operator()(const QueueNode& node_1, const QueueNode& node_2) const {
    if (node_1.f_score != node_2.f_score) {
      return node_1.f_score < node_2.f_score;
    }
    return node_1.id < node_2.id;
  }
};

template <size_t Capacity>
struct PriorityQueue {
  std::array<QueueNode, Capacity> data;
  size_t size = 0;

  PriorityQueue() : size(0) {}

  void add(node_id id, int32_t f_score) {
    if (size < Capacity) {
      QueueNode n = {id, f_score};
      data[size] = n;
      size++;
      std::push_heap(data.begin(), data.begin() + size, CompareFScore());
    }
  }

  QueueNode pop() {
    std::pop_heap(data.begin(), data.begin() + size, CompareFScore());
    QueueNode current = data[--size];

    return current;
  }

  void clear() { size = 0; }
};

}  // namespace pathfind