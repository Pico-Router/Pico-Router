cmake_minimum_required(VERSION 3.20.0)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(pico_router_sample)

target_sources(app PRIVATE
  src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/pathfind/astar.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/../src/fixtures/static_mock_graphs.cpp
)

target_compile_options(app PRIVATE
  -fno-threadsafe-statics
)

target_include_directories(app PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
)