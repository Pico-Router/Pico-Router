#include "pathfind/astar.h"

#include <gtest/gtest.h>

#include "../fixtures/mock_graphs.cc"

namespace pathfind {
namespace {

TEST(AstarOutline, FindsPathInMockGraph) {
  Graph graph = createMockGraph(MockGraphType::TRIANGLE);
  Astar planner;

  Path path = planner.calculatePath(graph, 0, 1);

  ASSERT_GT(path.length, 0U);
  EXPECT_EQ(path.nodes[0], 0U);
  EXPECT_EQ(path.nodes[path.length - 1], 1U);
}

TEST(AstarOutline, ReturnsEmptyPathForUnreachableGoal) {
  Graph graph = createMockGraph(MockGraphType::DISCONNECTED);
  Astar planner;

  // Node 999 has no incoming edges in the Mock graph setup.
  Path path = planner.calculatePath(graph, 0, 999);

  EXPECT_EQ(path.length, 0U);
}

}  // namespace
}  // namespace pathfind
