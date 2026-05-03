#pragma once

#include <cmath>
#include <cstdint>

#include "graph.h"

namespace pathfind {

// straight line distance in coordinate space. saturates to uint16_t to match Edge::cost
// typing requires x/y in the same units as edge weights for admissibility
inline uint16_t euclidean_heuristic(const Graph& g, node_id from, node_id to) {
  const Node* a = g.getNode(from);
  const Node* b = g.getNode(to);
  if (!a || !b) {
    return 0;
  }
  const int64_t dx = static_cast<int64_t>(a->x) - static_cast<int64_t>(b->x);
  const int64_t dy = static_cast<int64_t>(a->y) - static_cast<int64_t>(b->y);
  const double d = std::hypot(static_cast<double>(dx), static_cast<double>(dy));
  if (d >= static_cast<double>(UINT16_MAX)) {
    return UINT16_MAX;
  }
  return static_cast<uint16_t>(std::llround(d));
}

}  // namespace pathfind
