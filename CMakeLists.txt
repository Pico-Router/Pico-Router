cmake_minimum_required(VERSION 3.13)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(pico_router C CXX ASM)

pico_sdk_init()

add_executable(router
  src/main.cc
  src/pathfind/astar.cc
)

target_include_directories(router PRIVATE
  include
)

target_link_libraries(router
  pico_stdlib
)

pico_enable_stdio_uart(router 1)
pico_enable_stdio_usb(router 0)

pico_add_extra_outputs(router)