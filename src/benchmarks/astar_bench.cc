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
  std::vector<uint64_t> samples(sample_size);

  for (int i = 0; i < sample_size; i++) {
    // start timer
    timer.restart();
    // run algorithm
    Path route = router.calculatePath(bench_graph, 0, 2);
    // record time
    samples[i] = timer.nanoSeconds();
  }

  uint64_t min_time = *std::min_element(samples.begin(), samples.end());
  uint64_t max_time = *std::max_element(samples.begin(), samples.end());

  double total_time = std::accumulate(samples.begin(), samples.end(), 0.0);
  double average_time = total_time / sample_size;

  uart::write("Bench finished.\n");

  printf("Min execution time: %llu ns\n", (unsigned long long)min_time);
  printf("Max execution time: %llu ns\n", (unsigned long long)max_time);
  printf("Average execution time: %.2f ns\n", average_time);
}
