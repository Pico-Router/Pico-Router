#include "pathfind/path.h"

#include <gtest/gtest.h>

namespace pathfind {
namespace {

TEST(PathOutline, AddIncrementsLengthAndStoresNode) {
  Path path;

  EXPECT_TRUE(path.add(42));
  ASSERT_EQ(path.length, 1U);
  EXPECT_EQ(path.nodes[0], 42U);
}

TEST(PathOutline, ReverseReordersNodes) {
  Path path;
  path.add(1);
  path.add(2);
  path.add(3);

  path.reverse();

  ASSERT_EQ(path.length, 3U);
  EXPECT_EQ(path.nodes[0], 3U);
  EXPECT_EQ(path.nodes[1], 2U);
  EXPECT_EQ(path.nodes[2], 1U);
}

}  // namespace
}  // namespace pathfind
