#include <iostream>

#include "benchmarks/astar_bench.h"
#include "demo/astar_demo.h"
#include "platform/system_init.h"

int main() {
  platform_init();
  System global_system;
  demo::astar_demo main_demo;
  main_demo.run(global_system);

  while (true) {
    platform_sleep_ms(1000);
  };
}