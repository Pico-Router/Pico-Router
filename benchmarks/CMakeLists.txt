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
  ../src/pathfind/astar.cpp
  ../src/fixtures/dynamic_grid_graph.cpp
)

target_include_directories(run_benchmarks PRIVATE ../include)
target_link_libraries(run_benchmarks PRIVATE benchmark::benchmark)
target_compile_definitions(run_benchmarks PRIVATE BUILD_BENCH)

# HISTORIC BENCHMARK BUILD CONFIG
function(add_benchmark_target target_name implementation_dir version_macro)
  add_executable(${target_name}
    historic_bench.cpp
    ${implementation_dir}/src/astar.cpp
  )

  target_include_directories(${target_name} PRIVATE
    ${implementation_dir}/include
    ${CMAKE_SOURCE_DIR}/include/pathfind
  )

  target_link_libraries(${target_name} PRIVATE
    benchmark::benchmark
  )

  target_compile_definitions(${target_name} PRIVATE
    BUILD_BENCH
    ${version_macro}
  )
endfunction()

add_benchmark_target(
  run_historic_benchmarks_v01
  ${CMAKE_CURRENT_SOURCE_DIR}/historic/v1
  HISTORIC_V1
)

add_benchmark_target(
  run_historic_benchmarks_v02
  ${CMAKE_CURRENT_SOURCE_DIR}/historic/v2
  HISTORIC_V2
)
