#include <string_view>

#include "benchmarks/astar_bench.h"
#include "platform/uart.h"

namespace demo {

class astar_demo {
 public:
  void run(System& system);

 private:
  void print_header();
};

}  // namespace demo