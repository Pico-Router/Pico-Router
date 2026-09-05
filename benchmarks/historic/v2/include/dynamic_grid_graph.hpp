#pragma once

#include "graph.hpp"

namespace pathfind {

enum class ObstaclePattern { NONE, RANDOM_DENSITY, ZIGZAG_BARRIERS };

struct GridConfig {
  uint32_t width{100};
  uint32_t height{100};
  float obstacle_density{0.2f};
  uint32_t seed{42};
  ObstaclePattern pattern{ObstaclePattern::RANDOM_DENSITY};
};

Graph generateGridGraph(const GridConfig& config);

}  // namespace pathfind
