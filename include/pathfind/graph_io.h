#pragma once

/**
 * GraphIO covers:
 * 1. Transport — read a contiguous blob from storage (HAL function)
 * 2. Deserialize / materialize — copy blob bytes into a pathfind::Graph
 * 3. Validate — (future)lightweight sanity check on the Graph instance
 *
 * THIS IS AN AI-GENERATED PRELIMINARY IMPLEMENTATION. CHANGE LATER!
 */

#include <cstddef>
#include <cstring>
#include <fstream>
#include <optional>
#include <string>
#include <type_traits>
#include <vector>

#include "pathfind/graph.h"

namespace pathfind {

struct GraphIO {
  // 1. Transport — read entire file into an owned byte buffer.
  static std::optional<std::vector<std::byte>> readFile(
      const std::string& path) {
    std::ifstream in(path, std::ios::binary | std::ios::ate);
    if (!in.is_open()) {
      return std::nullopt;
    }
    const auto end = in.tellg();
    if (end < 0) {
      return std::nullopt;
    }
    const auto size = static_cast<std::size_t>(end);
    in.seekg(0, std::ios::beg);
    std::vector<std::byte> buffer(size);
    if (size > 0U) {
      if (!in.read(reinterpret_cast<char*>(buffer.data()),
                   static_cast<std::streamsize>(size))) {
        return std::nullopt;
      }
    }
    return buffer;
  }

  // 2. Deserialize / materialize — trivial copy of the on-disk Graph layout.
  static std::optional<Graph> graphFromBytes(const std::byte* data,
                                             std::size_t size) {
    static_assert(std::is_trivially_copyable_v<Graph>,
                  "Graph must be memcpy-deserializable from packed bytes");
    const auto n = sizeof(Graph);
    if (data == nullptr || size < n) {
      return std::nullopt;
    }
    Graph graph{};
    std::memcpy(&graph, data, n);
    return graph;
  }

  static std::optional<Graph> graphFromBytes(
      const std::vector<std::byte>& blob) {
    return graphFromBytes(blob.data(), blob.size());
  }

  // Convenience: transport + materialize (caller still validates graph if
  // needed).
  static std::optional<Graph> loadGraphFromFile(const std::string& path) {
    auto blob = readFile(path);
    if (!blob) {
      return std::nullopt;
    }
    return graphFromBytes(*blob);
  }
};

}  // namespace pathfind
