#pragma once

#include "pathfind/graph.hpp"

namespace pathfind {

enum class MockGraphType {
  TRIANGLE,
  DIAMOND,
  DISCONNECTED,
  GRID_5X5,
  FULL_BUFFER
};

Graph const& createMockGraph(MockGraphType type);

}  // namespace pathfind