#include "benchmarks/astar_bench.h"

#include <stdio.h>

#include <algorithm>
#include <numeric>
#include <string>

#include "platform/uart.h"

using namespace benchmarks;

void astar_bench::compute() {
  TimeResults results{};
  results = time();

  printf("BENCHMARK RESULTS:");
  printf(R"(
╔═══════════╦═════════════╗
║ Exc. Time ║ Nanoseconds ║
╠═══════════╬═════════════╣
║ Min       ║ %-11llu ║
║ Max       ║ %-11llu ║
║ Avg       ║ %-11llu ║
╚═══════════╩═════════════╝
)",
         (unsigned long long)results.min_time,
         (unsigned long long)results.max_time,
         (unsigned long long)results.average_time);
}

TimeResults astar_bench::time() {
  // setup
  steady_clock_timer timer;
  TimeResults results{};
  static uint64_t samples[sample_size];

  for (int i = 0; i < sample_size; i++) {
    // start timer
    timer.restart();
    // run algorithm
    pathfind::Path route = system_.router().calculatePath(bench_graph_, 0, 2);
    // record time
    samples[i] = timer.nanoSeconds();
  }

  // calculate times
  results.min_time = *std::min_element(samples, samples + sample_size);
  results.max_time = *std::max_element(samples, samples + sample_size);

  uint64_t total_time =
      std::accumulate(samples, samples + sample_size, uint64_t(0));
  results.average_time = (total_time + sample_size / 2) / sample_size;

  return results;
};
