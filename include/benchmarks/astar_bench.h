#pragma once

#include <cstdint>

#include "pathfind/astar.h"
#include "pathfind/graph.h"
#include "steady_clock_timer.h"

namespace benchmarks {

class astar_bench {
 public:
  void compute();
  const int sample_size = 5000;
};

}  // namespace benchmarks
