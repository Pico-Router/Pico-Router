#include <iostream>

#include "benchmarks/astar_bench.h"
#include "platform/system_init.h"

int main() {
  platform_init();
  System global_system;
  benchmarks::astar_bench b;
  while (true) {
    platform_sleep_ms(3000);
    b.compute(global_system);
  };
}