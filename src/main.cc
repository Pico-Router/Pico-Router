#include "benchmarks/astar_bench.h"
#include "pico/stdlib.h"

int main() {
  stdio_init_all();
  printf("Booted\n");
  benchmarks::astar_bench bench;
  (void)bench.compute();
  printf("Program finished succesfully\n");
  return 0;
}