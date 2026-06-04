cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

option(BUILD_PICO "Build for Raspberry Pi Pico" OFF)

if(BUILD_PICO)
  include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()

project(pico-router C CXX ASM)

set(COMMON_SOURCES
  src/main.cc
  src/pathfind/astar.cc
  src/benchmarks/astar_bench.cc
  src/fixtures/mock_graphs.cc
  src/demo/astar_demo.cc
)

if(BUILD_PICO)

  pico_sdk_init()

  add_executable(router
    ${COMMON_SOURCES}
    platform/pico/system_init_pico.cc
    platform/pico/uart_pico.cc
  )

  target_link_libraries(router
    pico_stdlib
  )

  pico_enable_stdio_uart(router 0)
  pico_enable_stdio_usb(router 1)

  pico_add_extra_outputs(router)

else()

  add_executable(router
    ${COMMON_SOURCES}
    platform/host/system_init_host.cc
    platform/host/uart_host.cc
  )

endif()

target_include_directories(router PRIVATE include)

# latest version macro
execute_process(
  COMMAND git describe --tags --abbrev=0
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  OUTPUT_VARIABLE GIT_VERSION
  OUTPUT_STRIP_TRAILING_WHITESPACE
  ERROR_QUIET
)

if(NOT GIT_VERSION)
  set(GIT_VERSION "v0.0.0-unknown")
endif()

target_compile_definitions(router PRIVATE LATEST_VERSION="${GIT_VERSION}")