#include "fixtures/static_mock_graphs.hpp"
#include "pathfind/astar.hpp"
#include "platform/system_init.hpp"
#include "platform/uart.hpp"

int main() {
  platform_init();

  pathfind::Graph graph =
      pathfind::createMockGraph(pathfind::MockGraphType::GRID_5X5);
  pathfind::Astar planner;

  auto path = planner.calculatePath(graph, 0, 24);

  uart::write("PICO ROUTER DEMO " LATEST_VERSION "\n");
  uart::write("Path: ");

  for (size_t i = 0; i < path.length; i++) {
    pathfind::node_id node_int = path.nodes[i];

    char buf[16];
    snprintf(buf, sizeof(buf), "%u ", static_cast<unsigned int>(node_int));
    uart::write(buf);
  }
  uart::write("\n");

  while (true) {
    platform_sleep_ms(1000);
  };

  return 0;
}