#include <string_view>

#include "benchmarks/astar_bench.hpp"
#include "platform/uart.hpp"

namespace demo {

class astar_demo {
 public:
  void run(System& system);

 private:
  void print_header();
};

}  // namespace demo