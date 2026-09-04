#include <benchmark/benchmark.h>

#include <cstdlib>

#include "fixtures/dynamic_grid_graph.hpp"
#include "pathfind/astar.hpp"
#include "pathfind/generated_config.hpp"

static void BM_Astar_Grid(benchmark::State& state) {
  const uint32_t size = state.range(0);
  const float density = static_cast<float>(state.range(1)) / 100.0f;

  if (static_cast<size_t>(size) * size > pathfind::config::MAX_NODES_) {
    std::fprintf(
        stderr, "Benchmark requires %zu nodes, but MAX_NODES_ is %zu\n",
        static_cast<size_t>(size) * size, pathfind::config::MAX_NODES_);
    std::abort();
  }

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