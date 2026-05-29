#include "benchmarks/astar_bench.h"

#include <stdio.h>

#include "../tests/fixtures/mock_graphs.cc"

using namespace benchmarks;
using namespace pathfind;

summary astar_bench::compute() {
  printf("Bench started\n");
  Graph const bench_graph = createMockGraph(MockGraphType::TRIANGLE);
  Astar router;
  steady_clock_timer timer;
  Path route = router.calculatePath(bench_graph, 0, 2);
  printf("Execution time was %llu nanoseconds.\n",
         static_cast<unsigned long long>(timer.nanoSeconds()));
  (void)route;
  printf("Bench finished\n");
  return summary{};
}
