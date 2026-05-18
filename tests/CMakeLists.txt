include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
  pathfind/astar_test.cc
  pathfind/path_test.cc

  ../src/pathfind/astar.cc
)

target_include_directories(run_tests PRIVATE ../include)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)