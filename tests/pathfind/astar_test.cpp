#include "pathfind/astar.hpp"

#include <gtest/gtest.h>

#include "fixtures/dynamic_grid_graph.hpp"
#include "fixtures/static_mock_graphs.hpp"

namespace pathfind {
namespace {

TEST(AstarTest, FindsPathInMockGraph) {
  Graph graph = createMockGraph(MockGraphType::TRIANGLE);
  Astar router;
  Path path = router.calculatePath(graph, 0, 1);

  ASSERT_GT(path.length, 0U);
  EXPECT_EQ(path.nodes[0], 0U);
  EXPECT_EQ(path.nodes[path.length - 1], 1U);
}

TEST(AstarTest, ReturnsEmptyPathForUnreachableGoal) {
  Graph graph = createMockGraph(MockGraphType::DISCONNECTED);
  Astar router;

  Path path = router.calculatePath(graph, 0, 999);

  EXPECT_EQ(path.length, 0U);
}

TEST(AstarTest, FindsPathInGeneratedGrid) {
  GridConfig config{.width = 50,
                    .height = 50,
                    .obstacle_density = 0.0f,
                    .seed = 1234,
                    .pattern = ObstaclePattern::RANDOM_DENSITY};
  Graph graph = generateGridGraph(config);
  Astar router;

  node_id start_id = 0;
  node_id goal_id = (config.width * config.height) - 1;

  ASSERT_NE(graph.getNode(start_id), nullptr);
  ASSERT_NE(graph.getNode(goal_id), nullptr);

  Path path = router.calculatePath(graph, start_id, goal_id);

  EXPECT_EQ(graph.getNodeCount(), config.width * config.height);
  ASSERT_GT(path.length, 0U);
  EXPECT_EQ(path.nodes[0], start_id);
  EXPECT_EQ(path.nodes[path.length - 1], goal_id);
}
}  // namespace
}  // namespace pathfind
