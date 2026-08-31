#include "fixtures/dynamic_grid_graph.hpp"

#include <random>

#include "pathfind/graph.hpp"

namespace pathfind {

Graph generateGridGraph(const GridConfig& config) {
  Graph graph;

  uint32_t current_node_index = 0;
  uint32_t current_edge_offset = 0;

  for (uint32_t y = 0; y < config.height; ++y) {
    for (uint32_t x = 0; x < config.width; ++x) {
      if (current_node_index >= MAX_NODES) break;

      Node& node = graph.nodes[current_node_index];
      node.x = static_cast<int32_t>(x);
      node.y = static_cast<int32_t>(y);
      node.edge_offset = current_edge_offset;
      node.edge_count = 0;

      int dx[] = {0, 0, -1, 1};
      int dy[] = {-1, 1, 0, 0};

      for (int i = 0; i < 4; ++i) {
        int nx = static_cast<int>(x) + dx[i];
        int ny = static_cast<int>(y) + dy[i];

        // bounds check
        if (nx >= 0 && nx < static_cast<int>(config.width) && ny >= 0 &&
            ny < static_cast<int>(config.height)) {
          if (current_edge_offset < MAX_EDGES) {
            uint32_t neighbor_index = ny * config.width + nx;
            graph.edges[current_edge_offset] =
                Edge{.target = neighbor_index, .cost = 10};
            current_edge_offset++;
            node.edge_count++;
          }
        }
      }
      current_node_index++;
    }
  }
  return graph;
}

}  // namespace pathfind