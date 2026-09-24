#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#include "fixtures/static_mock_graphs.hpp"
#include "pathfind/astar.hpp"

int main() {
  printk("=== APP STARTED ===\n");

  pathfind::Graph graph =
      pathfind::createMockGraph(pathfind::MockGraphType::GRID_5X5);

  pathfind::Astar planner;
  const auto path = planner.calculatePath(graph, 0, 24);

  printk("Path: ");

  for (size_t index = 0; index < path.length; ++index) {
    printk("%u ", static_cast<unsigned int>(path.nodes[index]));
  }

  printk("\n");
  printk("=== APP FINISHED ===\n");

  while (true) {
    k_sleep(K_SECONDS(1));
  }
}