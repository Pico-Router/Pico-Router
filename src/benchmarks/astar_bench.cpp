#include <benchmark/benchmark.h>

#include "fixtures/dynamic_grid_graph.hpp"
#include "pathfind/astar.hpp"

static void BM_Astar_Grid100x100(benchmark::State& state) {
  pathfind::GridConfig config{
      .width = 100, .height = 100, .obstacle_density = 0.15f, .seed = 42};
  const pathfind::Graph graph = pathfind::generateGridGraph(config);
  pathfind::Astar planner;

  for (auto _ : state) {
    auto path = planner.calculatePath(graph, 0, 9999);
    benchmark::DoNotOptimize(path);
  }
}
BENCHMARK(BM_Astar_Grid100x100);

BENCHMARK_MAIN();