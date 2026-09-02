include(FetchContent)
FetchContent_Declare(
  googlebenchmark
  URL https://github.com/google/benchmark/archive/refs/tags/v1.9.5.zip
)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
set(BENCHMARK_ENABLE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googlebenchmark)

add_executable(run_benchmarks
  astar_bench.cpp
  ../pathfind/astar.cpp
  ../fixtures/dynamic_grid_graph.cpp
)

target_include_directories(run_benchmarks PRIVATE ../../include)
target_link_libraries(run_benchmarks PRIVATE benchmark::benchmark)
target_compile_definitions(run_benchmarks PRIVATE BUILD_BENCH)