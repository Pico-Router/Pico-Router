#include "benchmarks/astar_bench.h"

#include <stdio.h>

#include <algorithm>
#include <numeric>
#include <string>

#include "../tests/fixtures/mock_graphs.cc"
#include "platform/uart.h"

using namespace benchmarks;
using namespace pathfind;

void astar_bench::compute() {
  uart::write("Bench started.\n");

  // setup
  Astar router;
  Graph const bench_graph = createMockGraph(MockGraphType::TRIANGLE);
  steady_clock_timer timer;
  uint64_t samples[sample_size];

  for (int i = 0; i < sample_size; i++) {
    // run algorithm
    Path route = router.calculatePath(bench_graph, 0, 2);
    // record time
    samples[i] = timer.nanoSeconds();
  }

  uint64_t min_time = *std::min_element(samples, samples + sample_size);
  uint64_t max_time = *std::max_element(samples, samples + sample_size);

  double total_time = std::accumulate(samples, samples + sample_size, 0.0);
  double average_time = total_time / sample_size;

  uart::write("Bench finished.\n");

  uart::write("Min execution time: ");
  uart::write(std::to_string(min_time));
  uart::write(" ns\n");

  uart::write("Max execution time: ");
  uart::write(std::to_string(max_time));
  uart::write(" ns\n");

  uart::write("Average execution time: ");
  uart::write(std::to_string(average_time));
  uart::write(" ns\n");
}
