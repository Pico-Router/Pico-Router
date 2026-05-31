cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

project(pico-router C CXX ASM)

option(BUILD_PICO "Build for Raspberry Pi Pico" OFF)

set(COMMON_SOURCES
  src/main.cc
  src/pathfind/astar.cc
  src/benchmarks/astar_bench.cc
)

if(BUILD_PICO)

  include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
  pico_sdk_init()

  add_executable(router
    ${COMMON_SOURCES}
    platform/pico/init_pico.cc
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
    platform/host/init_host.cc
    platform/host/uart_host.cc
  )

endif()

target_include_directories(router PRIVATE include)
