#include "fixtures/static_mock_graphs.hpp"

#include <memory>

#include "pathfind/graph.hpp"

namespace pathfind {

Graph const& createMockGraph(MockGraphType type) {
  static const Graph triangle = [] {
    Graph graph{};

    // NODE 0
    graph.nodes[0] = {0, 0, 0, 2};
    graph.edges[0] = {1, 10};
    graph.edges[1] = {2, 20};

    // NODE 1
    graph.nodes[1] = {10, 0, 2, 2};
    graph.edges[2] = {0, 10};
    graph.edges[3] = {2, 10};

    // NODE 2
    graph.nodes[2] = {0, 20, 4, 2};
    graph.edges[4] = {0, 20};
    graph.edges[5] = {1, 20};

    return graph;
  }();

  static const Graph disconnected = [] {
    Graph graph{};

    // nodes 0 and 1 have no outgoing edges
    graph.nodes[0] = {0, 0, 0, 0};
    graph.nodes[1] = {10, 0, 0, 0};

    return graph;
  }();

  switch (type) {
    case MockGraphType::TRIANGLE:
      return triangle;

    case MockGraphType::DISCONNECTED:
      return disconnected;

    default:
      return disconnected;
  }
}

}  // namespace pathfind
