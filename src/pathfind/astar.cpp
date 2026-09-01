#include "pathfind/astar.hpp"

#include <cassert>

using namespace pathfind;

Path Astar::calculatePath(const Graph& graph, node_id start_id,
                          node_id goal_id) {
  // empty path to return on failure
  Path empty_path;

  // initialzation
  open_list.clear();
  closed_list.reset();
  gScore.fill(INT32_MAX);

  gScore[start_id] = 0;
  uint32_t start_heuristic = euclidean_heuristic(graph, start_id, goal_id);
  open_list.add(start_id, start_heuristic);

  // expansion loop
  while (open_list.size > 0) {
    QueueNode current = open_list.pop();

    if (current.id == goal_id) {
      return reconstructPath(current.id, start_id);
    }

    closed_list[current.id] = true;

    const Node* node = graph.getNode(current.id);
    if (!node) {
      continue;
    }

    uint32_t edge_count = node->edge_count;
    uint32_t edge_offset = node->edge_offset;

    for (uint32_t i = 0; i < edge_count; ++i) {
      const Edge& edge = graph.edges[edge_offset + i];
      node_id neighbor_id = edge.target;

      // skip if already in closed list
      if (closed_list[neighbor_id]) {
        continue;
      }

      // avoid int overflow
      if (gScore[current.id] == INT32_MAX) continue;
      uint32_t tentative_g = gScore[current.id] + edge.cost;

      // new best path found
      if (tentative_g < gScore[neighbor_id]) {
        came_from_list[neighbor_id] = current.id;
        gScore[neighbor_id] = tentative_g;
        int32_t tentative_f =
            tentative_g + euclidean_heuristic(graph, neighbor_id, goal_id);
        open_list.add(neighbor_id, tentative_f);
      }
    }
  }

  return empty_path;
}

Path Astar::reconstructPath(node_id current, node_id start) {
  assert(current < came_from_list.size() &&
         "reconstructPath called with out of bounds node_id");

  Path reconstructed_path;

  while (current != start) {
    if (!reconstructed_path.add(current)) {
      return reconstructed_path;
    }
    current = came_from_list[current];
  }
  reconstructed_path.add(start);
  reconstructed_path.reverse();

  return reconstructed_path;
}
