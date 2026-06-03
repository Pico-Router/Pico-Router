#pragma once

#include "pathfind/graph.h"

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