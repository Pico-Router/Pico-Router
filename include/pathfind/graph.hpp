#pragma once

#include <array>
#include <cstddef>
#include <cstdint>

namespace pathfind {

using node_id = uint32_t;

static constexpr size_t MAX_NODES = 10000;
static constexpr size_t MAX_EDGES = 40000;

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
  std::array<Node, MAX_NODES> nodes{};
  std::array<Edge, MAX_EDGES> edges{};

  const Node* getNode(node_id id) const {
    if (id < nodes.size()) {
      return &nodes[id];
    }
    return nullptr;
  }
};

}  // namespace pathfind
