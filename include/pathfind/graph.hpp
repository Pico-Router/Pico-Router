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

struct Coordinates {
  int32_t x;
  int32_t y;
};

struct Node {
  Coordinates coordinates;
  uint32_t edge_offset;
  uint32_t edge_count;
};

struct GraphHeader {
  uint32_t format_version;
  uint32_t header_size;
  uint32_t graph_size;
};

struct EdgeRange {
  const Edge* data;
  size_t size;

  const Edge* begin() const { return data; }
  const Edge* end() const { return data + size; }
};

struct Graph {
 public:
  GraphHeader header;
  std::array<Node, config::MAX_NODES_> nodes{};
  std::array<Edge, config::MAX_EDGES_> edges{};

  const Node* getNode(node_id id) const {
    if (id < nodes.size()) {
      return &nodes[id];
    }
    return nullptr;
  }

  EdgeRange getNeighbors(node_id id) const {
    const Node& node = nodes[id];
    return EdgeRange{edges.data() + node.edge_offset, node.edge_count};
  }

  Coordinates getCoordinates(node_id id) const { return nodes[id].coordinates; }

  size_t getNodeCount() const { return node_count_; }
  void incrementNodeCount() { ++node_count_; }

 private:
  size_t node_count_ = 0;
};

}  // namespace pathfind
