#include "fixtures/mock_graphs.h"

#include <memory>

#include "pathfind/graph.h"

namespace pathfind {

Graph const& createMockGraph(MockGraphType type) {
  static Graph graph{};

  switch (type) {
    case MockGraphType::TRIANGLE:
      // note: nodes are missing x/y coordinates
      // NODE 0
      graph.edges[1] = {1, 10, 2};
      graph.edges[2] = {2, 20, 0};
      graph.nodes[0].first_edge_index = 1;

      // NODE 1
      graph.edges[3] = {0, 10, 4};
      graph.edges[4] = {2, 10, 0};
      graph.nodes[1].first_edge_index = 3;

      // NODE 2
      graph.edges[5] = {0, 20, 6};
      graph.edges[6] = {1, 20, 0};
      graph.nodes[2].first_edge_index = 5;
      break;

    case MockGraphType::DISCONNECTED:
      // NODE 0
      graph.nodes[0].first_edge_index = 0;
      // NODE 1
      graph.nodes[1].first_edge_index = 0;
      break;

    default:
      break;
  }
  return graph;
}

}  // namespace pathfind
