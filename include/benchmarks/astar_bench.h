#pragma once

#include <cstdint>

#include "pathfind/graph.h"
#include "platform/system_init.h"
#include "steady_clock_timer.h"

namespace benchmarks {

class astar_bench {
 public:
  void compute(System& global_system);
  static constexpr int sample_size = 5000;
};

}  // namespace benchmarks
