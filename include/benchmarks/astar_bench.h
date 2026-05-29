#pragma once

#include <cstdint>

#include "pathfind/astar.h"
#include "pathfind/graph.h"
#include "steady_clock_timer.h"

namespace benchmarks {

struct run_result {
  uint64_t time_ns;

  uint32_t expanded_nodes;
  uint32_t peak_open_set;
  uint32_t peak_closed_set;

  uint32_t path_length;
  bool found;
};

struct summary {
  uint64_t min_ns;
  uint64_t max_ns;

  double average_ns;
  double median_ns;

  uint64_t p95_ns;

  double average_expanded;
};

class astar_bench {
 public:
  summary compute();
};

}  // namespace benchmarks
