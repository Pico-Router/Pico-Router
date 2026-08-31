cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON) 

option(BUILD_PICO "Build for Raspberry Pi Pico" OFF)
option(BUILD_BENCH "Build Google Benchmarks" OFF)

if(BUILD_PICO)
  include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)
endif()

project(pico-router C CXX ASM)

include(CTest)

set(COMMON_SOURCES
  src/main.cpp
  src/pathfind/astar.cpp
  src/fixtures/static_mock_graphs.cpp
)

if(BUILD_PICO)

  pico_sdk_init()

  add_executable(router
    ${COMMON_SOURCES}
    src/platform/pico/system_init_pico.cpp
    src/platform/pico/uart_pico.cpp
  )

  target_link_libraries(router
    pico_stdlib
  )

  pico_enable_stdio_uart(router 1)
  pico_enable_stdio_usb(router 0)

  pico_add_extra_outputs(router)

else()

  add_executable(router
    ${COMMON_SOURCES}
    src/platform/host/system_init_host.cpp
    src/platform/host/uart_host.cpp
  )
  
  if(BUILD_BENCH)
    add_subdirectory(src/benchmarks)
  endif()

endif()

target_include_directories(router PRIVATE include)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  target_compile_options(router PRIVATE 
    -Wall 
    -Wextra 
    -Wpedantic
    -Wconversion
    -Wshadow
  )
endif()

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

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()
