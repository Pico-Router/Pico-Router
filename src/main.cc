#include <iostream>

#include "benchmarks/astar_bench.h"
#include "platform/init.h"

int main() {
  platform_init();
  benchmarks::astar_bench b;
  b.compute();
  while (true) {
  };
}