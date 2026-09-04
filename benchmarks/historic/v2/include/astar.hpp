#pragma once

#include <bitset>

#include "generated_config.hpp"
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

#ifdef BUILD_BENCH
  size_t nodesExpanded() const { return nodes_expanded_; }
  size_t edgesExamined() const { return edges_examined_; }
#endif

 private:
  std::array<node_id, config::MAX_NODES_> gScore;

  // todo: add no parent sentinal
  std::array<node_id, config::MAX_NODES_> came_from_list;
  PriorityQueue<config::MAX_NODES_> open_list;
  std::bitset<config::MAX_NODES_> closed_list;
  Path reconstructPath(node_id current, node_id start);

#ifdef BUILD_BENCH
  size_t nodes_expanded_ = 0;
  size_t edges_examined_ = 0;
#endif
};

}  // namespace pathfind
