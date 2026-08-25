#pragma once

#include <bitset>

#include "graph.hpp"
#include "heuristic.hpp"
#include "path.hpp"
#include "priority_queue.hpp"

/**
 * Implementation of A* algorithm
 * Pseudocode: https://en.wikipedia.org/wiki/A*_search_algorithm#Pseudocode
 */

namespace pathfind {

class Astar {
 public:
  Path calculatePath(const Graph& graph, node_id start, node_id goal);

 private:
  std::array<node_id, MAX_NODES> gScore;

  std::array<node_id, MAX_NODES>
      came_from_list;  // todo: add no parent sentinal
  PriorityQueue<MAX_NODES> open_list;
  std::bitset<MAX_NODES> closed_list;
  Path reconstructPath(node_id current, node_id start);
};

}  // namespace pathfind
