#include <iostream>

#include "benchmarks/astar_bench.hpp"
#include "demo/astar_demo.hpp"
#include "platform/system_init.hpp"

int main() {
  platform_init();
  System global_system;
  demo::astar_demo main_demo;

  await_input();
  main_demo.run(global_system);

  while (true) {
    platform_sleep_ms(1000);
  };
}