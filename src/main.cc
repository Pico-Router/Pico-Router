#include <iostream>

#include "pathfind/astar.h"
#include "pathfind/graph_io.h"

int main(int argc, char** argv) {
  // Demo. Delete later.
  const std::string path = "data/sample_graph.bin";

  auto graphOpt = pathfind::GraphIO::loadGraphFromFile(path);
  if (!graphOpt) {
    std::fprintf(stderr, "Failed to load graph from %s\n", path.c_str());
    return 1;
  }

  pathfind::Graph const graph = std::move(*graphOpt);

  int nodeCount = 0;
  for (size_t i = 0; i < pathfind::MAX_NODES; i++) {
    if (graph.nodes[i].first_edge_index != 0 || i == 0) {
      nodeCount++;
    }
  }
  std::cout << "Graph has " << nodeCount << " nodes\n";

  pathfind::Astar router;
  pathfind::Path route = router.calculatePath(graph, 1, 4);

  std::cout << "Success!\n" << "Path: " << route << "\n";

  return 0;
}