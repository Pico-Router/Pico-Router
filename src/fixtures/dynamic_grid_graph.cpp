#include "fixtures/dynamic_grid_graph.hpp"

#include <random>

#include "pathfind/graph.hpp"

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
                       uint32_t& current_node_index, Node& node,
                       std::bernoulli_distribution& obstacle_dist,
                       std::mt19937& engine) {
  constexpr std::array<int32_t, 4> dx = {0, 0, -1, 1};
  constexpr std::array<int32_t, 4> dy = {-1, 1, 0, 0};
  constexpr uint32_t DEFAULT_EDGE_COST = 10;

  for (size_t i = 0; i < 4; ++i) {
    int32_t nx = static_cast<int32_t>(x) + dx[i];
    int32_t ny = static_cast<int32_t>(y) + dy[i];

    if (isInBounds(nx, ny, config.width, config.height)) {
      if (current_edge_offset >= MAX_EDGES) break;

      uint32_t neighbor_index = toNodeIndex(nx, ny, config.width);

      bool is_obstacle = obstacle_dist(engine);
      if (current_node_index == 0 ||
          current_node_index == (config.height * config.width) - 1 ||
          !is_obstacle) {
        graph.edges[current_edge_offset] =
            Edge{.target = neighbor_index, .cost = DEFAULT_EDGE_COST};

        ++current_edge_offset;
        ++node.edge_count;
      }
    }
  }
}

Graph generateGridGraph(const GridConfig& config) {
  std::mt19937 engine(config.seed);
  std::bernoulli_distribution obstacle_dist(config.obstacle_density);

  Graph graph{};
  uint32_t current_node_index = 0;
  uint32_t current_edge_offset = 0;

  for (uint32_t y = 0; y < config.height; ++y) {
    for (uint32_t x = 0; x < config.width; ++x) {
      if (current_node_index >= MAX_NODES) return graph;

      Node& node = graph.nodes[current_node_index];
      node.x = static_cast<int32_t>(x);
      node.y = static_cast<int32_t>(y);
      node.edge_offset = current_edge_offset;
      node.edge_count = 0;

      populateNodeEdges(graph, x, y, config, current_edge_offset,
                        current_node_index, node, obstacle_dist, engine);

      current_node_index++;
      graph.incrementNodeCount();
    }
  }

  return graph;
}

}  // namespace pathfind