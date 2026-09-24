zephyr_library(pico_router)

zephyr_library_sources(
  ${ZEPHYR_CURRENT_MODULE_DIR}/src/pathfind/astar.cpp
)

zephyr_library_include_directories(
  ${ZEPHYR_CURRENT_MODULE_DIR}/include
)

zephyr_library_compile_options(
  -Wall
  -Wextra
  -Wshadow
)