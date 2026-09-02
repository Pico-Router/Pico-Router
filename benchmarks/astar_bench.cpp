#include <benchmark/benchmark.h>

#include "fixtures/dynamic_grid_graph.hpp"
#include "pathfind/astar.hpp"

static void BM_Astar_Grid(benchmark::State& state) {
  const uint32_t size = state.range(0);
  const float density = static_cast<float>(state.range(1)) / 100.0f;

  pathfind::GridConfig config{
      .width = size,
      .height = size,
      .obstacle_density = density,
      .seed = 82,
  };

  const pathfind::Graph graph = pathfind::generateGridGraph(config);
  pathfind::Astar planner;

  for (auto _ : state) {
    auto path = planner.calculatePath(graph, 0, size * size - 1);
    benchmark::DoNotOptimize(path);

    state.counters["Nodes"] = static_cast<double>(planner.nodesExpanded());
    state.counters["Edges"] = static_cast<double>(planner.edgesExamined());
  }
}

BENCHMARK(BM_Astar_Grid)
    ->Args({25, 0})
    ->Args({25, 50})
    ->Args({25, 90})
    ->Args({50, 0})
    ->Args({50, 50})
    ->Args({50, 90})
    ->Args({100, 0})
    ->Args({100, 50})
    ->Args({100, 90});

BENCHMARK_MAIN();