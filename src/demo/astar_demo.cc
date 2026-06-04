#include "demo/astar_demo.h"

#include <string_view>

#include "benchmarks/astar_bench.h"
#include "platform/uart.h"

void demo::astar_demo::run(System& system) {
  print_header();
  benchmarks::astar_bench b(system);
  b.compute();
};

void demo::astar_demo::print_header() {
  static constexpr std::string_view main_header = R"(
 /$$$$$$$  /$$                           /$$$$$$$                        /$$                        
| $$__  $$|__/                          | $$__  $$                      | $$                        
| $$  \ $$ /$$  /$$$$$$$  /$$$$$$       | $$  \ $$  /$$$$$$  /$$   /$$ /$$$$$$    /$$$$$$   /$$$$$$ 
| $$$$$$$/| $$ /$$_____/ /$$__  $$      | $$$$$$$/ /$$__  $$| $$  | $$|_  $$_/   /$$__  $$ /$$__  $$
| $$____/ | $$| $$      | $$  \ $$      | $$__  $$| $$  \ $$| $$  | $$  | $$    | $$$$$$$$| $$  \__/
| $$      | $$| $$      | $$  | $$      | $$  \ $$| $$  | $$| $$  | $$  | $$ /$$| $$_____/| $$      
| $$      | $$|  $$$$$$$|  $$$$$$/      | $$  | $$|  $$$$$$/|  $$$$$$/  |  $$$$/|  $$$$$$$| $$      
|__/      |__/ \_______/ \______/       |__/  |__/ \______/  \______/    \___/   \_______/|__/      
  )";

  uart::write(main_header);
  uart::write("\n");
  uart::write("Created and maintained by Victor Yanson\n");
};