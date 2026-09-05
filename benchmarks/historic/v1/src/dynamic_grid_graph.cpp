#include "fixtures/dynamic_grid_graph.hpp"

#include <array>
#include <random>

#include "generated_config.hpp"
#include "graph.hpp"

namespace pathfind {

constexpr bool isInBounds(int32_t x, int32_t y, uint32_t width,
                          uint32_t height) {
  return x >= 0 && x < static_cast<int32_t>(width) && y >= 0 &&
         y < static_cast<int32_t>(height);
}

constexpr uint32_t toNodeIndex(int32_t x, int32_t y, uint32_t width) {
  return static_cast<uint32_t>(y) * width + static_cast<uint32_t>(x);
}

void populateNodeEdges(Graph& graph, uint32_t x, uint32_t y,
                       const GridConfig& config, uint32_t& current_edge_offset,
                       uint32_t current_node_index, Node& node,
                       std::bernoulli_distribution& obstacle_dist,
                       std::mt19937& engine) {
  constexpr std::array<int32_t, 4> dx = {0, 0, -1, 1};
  constexpr std::array<int32_t, 4> dy = {-1, 1, 0, 0};
  constexpr uint16_t DEFAULT_EDGE_COST = 10;

  const bool is_start = current_node_index == 0;
  const bool is_goal = current_node_index == (config.height * config.width) - 1;

  bool has_edges = false;
  uint32_t previous_edge_index = 0;

  for (size_t i = 0; i < 4; ++i) {
    const int32_t nx = static_cast<int32_t>(x) + dx[i];
    const int32_t ny = static_cast<int32_t>(y) + dy[i];

    if (!isInBounds(nx, ny, config.width, config.height)) {
      continue;
    }

    // Reserve one slot for the sentinel edge.
    if (current_edge_offset >= MAX_EDGES - 1) {
      break;
    }

    if (!is_start && !is_goal && obstacle_dist(engine)) {
      continue;
    }

    const uint32_t edge_index = current_edge_offset++;

    graph.edges[edge_index] = Edge{
        static_cast<uint16_t>(toNodeIndex(nx, ny, config.width)),
        DEFAULT_EDGE_COST,
        edge_index,
    };

    if (!has_edges) {
      node.first_edge_index = edge_index;
      has_edges = true;
    } else {
      graph.edges[previous_edge_index].next_edge_index = edge_index;
    }

    previous_edge_index = edge_index;
  }

  if (has_edges) {
    // A self-referencing edge terminates the linked list.
    graph.edges[previous_edge_index].next_edge_index = previous_edge_index;
  } else {
    // Empty-node sentinel.
    node.first_edge_index = current_edge_offset;
  }

  graph.edges[current_edge_offset] = Edge{
      0,
      0,
      current_edge_offset,
  };

  ++current_edge_offset;
}

Graph generateGridGraph(const GridConfig& config) {
  std::mt19937 engine(config.seed);
  std::bernoulli_distribution obstacle_dist(config.obstacle_density);

  Graph graph{};

  uint32_t current_edge_offset = 0;
  uint32_t current_node_index = 0;

  for (uint32_t y = 0; y < config.height; ++y) {
    for (uint32_t x = 0; x < config.width; ++x) {
      if (current_node_index >= MAX_NODES) {
        return graph;
      }

      // Leave room for the sentinel edge.
      if (current_edge_offset >= MAX_EDGES - 1) {
        return graph;
      }

      Node& node = graph.nodes[current_node_index];

      node.x = static_cast<int32_t>(x);
      node.y = static_cast<int32_t>(y);
      node.first_edge_index = current_edge_offset;

      populateNodeEdges(graph, x, y, config, current_edge_offset,
                        current_node_index, node, obstacle_dist, engine);

      ++current_node_index;
    }
  }

  return graph;
}

}  // namespace pathfind