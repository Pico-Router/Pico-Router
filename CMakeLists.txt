cmake_minimum_required(VERSION 3.13)

project(pico_router C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
include(CTest)

# Add executable
file(GLOB SOURCES "src/*.cc" "src/pathfind/*.cc")
add_executable(${PROJECT_NAME} ${SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE include)

if(BUILD_TESTING)
  add_subdirectory(tests)
endif()