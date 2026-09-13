#include "fixtures/static_mock_graphs.hpp"

#include "pathfind/graph.hpp"

namespace pathfind {

Graph const& createMockGraph(MockGraphType type) {
  static const Graph triangle = [] {
    Graph graph{};

    // NODE 0
    graph.nodes[0] = {
        Coordinates{0, 0},
        0,
        2,
    };
    graph.edges[0] = {1, 10};
    graph.edges[1] = {2, 20};

    // NODE 1
    graph.nodes[1] = {
        Coordinates{10, 0},
        2,
        2,
    };
    graph.edges[2] = {0, 10};
    graph.edges[3] = {2, 10};

    // NODE 2
    graph.nodes[2] = {
        Coordinates{0, 20},
        4,
        2,
    };
    graph.edges[4] = {0, 20};
    graph.edges[5] = {1, 20};

    return graph;
  }();

  static const Graph disconnected = [] {
    Graph graph{};

    // Nodes 0 and 1 have no outgoing edges.
    graph.nodes[0] = {
        Coordinates{0, 0},
        0,
        0,
    };

    graph.nodes[1] = {
        Coordinates{10, 0},
        0,
        0,
    };

    return graph;
  }();

  static const Graph grid_5x5 = [] {
    Graph graph{};

    constexpr uint32_t GRID_SIZE = 5;
    constexpr uint32_t SPACING = 10;
    constexpr uint32_t EDGE_COST = 10;

    uint32_t edge_index = 0;

    for (uint32_t y = 0; y < GRID_SIZE; ++y) {
      for (uint32_t x = 0; x < GRID_SIZE; ++x) {
        const uint32_t id = y * GRID_SIZE + x;

        graph.nodes[id] = {
            Coordinates{
                static_cast<int32_t>(x * SPACING),
                static_cast<int32_t>(y * SPACING),
            },
            edge_index,
            0,
        };

        // Left
        if (x > 0) {
          graph.edges[edge_index++] = {
              id - 1,
              EDGE_COST,
          };
          ++graph.nodes[id].edge_count;
        }

        // Right
        if (x + 1 < GRID_SIZE) {
          graph.edges[edge_index++] = {
              id + 1,
              EDGE_COST,
          };
          ++graph.nodes[id].edge_count;
        }

        // Up
        if (y > 0) {
          graph.edges[edge_index++] = {
              id - GRID_SIZE,
              EDGE_COST,
          };
          ++graph.nodes[id].edge_count;
        }

        // Down
        if (y + 1 < GRID_SIZE) {
          graph.edges[edge_index++] = {
              id + GRID_SIZE,
              EDGE_COST,
          };
          ++graph.nodes[id].edge_count;
        }

        graph.incrementNodeCount();
      }
    }

    return graph;
  }();

  switch (type) {
    case MockGraphType::TRIANGLE:
      return triangle;

    case MockGraphType::DISCONNECTED:
      return disconnected;

    case MockGraphType::GRID_5X5:
      return grid_5x5;

    default:
      return disconnected;
  }
}

}  // namespace pathfind