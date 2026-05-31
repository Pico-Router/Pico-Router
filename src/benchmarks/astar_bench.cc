#include "benchmarks/astar_bench.h"

#include <stdio.h>

#include <string>

#include "../tests/fixtures/mock_graphs.cc"
#include "platform/uart.h"

using namespace benchmarks;
using namespace pathfind;

summary astar_bench::compute() {
  uart::write("Bench started.\n");

  Astar router;

  Graph const bench_graph = createMockGraph(MockGraphType::TRIANGLE);

  steady_clock_timer timer;
  Path route = router.calculatePath(bench_graph, 0, 2);
  unsigned long long nano_time =
      static_cast<unsigned long long>(timer.nanoSeconds());

  uart::write("Execution time was ");
  uart::write(std::to_string(nano_time));
  uart::write(" nanoseconds.\n");

  uart::write("Bench finished.\n");

  summary s;
  return s;
}
