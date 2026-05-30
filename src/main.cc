#include "benchmarks/astar_bench.h"
#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  benchmarks::astar_bench();
  while (true) {
  };
}