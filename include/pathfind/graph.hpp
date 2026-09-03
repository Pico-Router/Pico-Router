#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

#include "generated_config.hpp"

namespace pathfind {

using node_id = uint32_t;

struct Edge {
  uint32_t target;
  uint32_t cost;
};

struct Node {
  int32_t x;
  int32_t y;
  uint32_t edge_offset;
  uint32_t edge_count;
};

struct Graph {
 public:
  std::array<Node, config::MAX_NODES_> nodes{};
  std::array<Edge, config::MAX_EDGES_> edges{};

  const Node* getNode(node_id id) const {
    if (id < nodes.size()) {
      return &nodes[id];
    }
    return nullptr;
  }

  size_t getNodeCount() const { return node_count_; }
  void incrementNodeCount() { ++node_count_; }

 private:
  size_t node_count_ = 0;
};

}  // namespace pathfind
