include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(run_tests
  pathfind/astar_test.cpp
  pathfind/path_test.cpp

  ../src/pathfind/astar.cpp
)

target_include_directories(run_tests PRIVATE ../include)
target_link_libraries(run_tests PRIVATE GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests)