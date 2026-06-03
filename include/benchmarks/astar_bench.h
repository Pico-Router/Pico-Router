#pragma once

#include <cstdint>

#include "fixtures/mock_graphs.h"
#include "pathfind/graph.h"
#include "platform/system_init.h"
#include "steady_clock_timer.h"

namespace benchmarks {

struct TimeResults {
  uint64_t min_time, max_time, average_time;
};

class astar_bench {
 public:
  explicit astar_bench(System& system)
      : system_(system),
        bench_graph_(
            pathfind::createMockGraph(pathfind::MockGraphType::TRIANGLE)) {}

  void compute();

 private:
  TimeResults time();

  System& system_;
  pathfind::Graph const& bench_graph_;

  static constexpr int sample_size = 5000;
};

}  // namespace benchmarks
