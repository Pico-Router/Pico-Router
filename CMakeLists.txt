cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_router C CXX ASM)

pico_sdk_init()

add_executable(router
  src/main.cc
  src/pathfind/astar.cc
  src/benchmarks/astar_bench.cc
)

target_include_directories(router PRIVATE
  include
)

target_link_libraries(router
  pico_stdlib
)

target_compile_definitions(router PRIVATE
  PICO_RUNTIME_SKIP_INIT_BOOTROM_RESET=1
  PICO_RUNTIME_NO_INIT_BOOTROM_RESET=1
  PICO_RUNTIME_SKIP_INIT_PER_CORE_BOOTROM_RESET=1
  PICO_RUNTIME_NO_INIT_PER_CORE_BOOTROM_RESET=1
  PICO_RUNTIME_SKIP_INIT_BOOTROM_LOCKING_ENABLE=1
  PICO_BOOTROM_LOCKING_ENABLED=0
  PICO_RUNTIME_SKIP_INIT_EARLY_RESETS=1
  PICO_RUNTIME_SKIP_INIT_CLOCKS=1
  PICO_RUNTIME_SKIP_INIT_POST_CLOCK_RESETS=1
  PICO_RUNTIME_SKIP_INIT_PER_CORE_ENABLE_COPROCESSORS=1
)

pico_enable_stdio_uart(router 1)
pico_enable_stdio_usb(router 0)

pico_add_extra_outputs(router)
