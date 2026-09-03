#include <cstdio>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include "pathfind/astar.hpp"
#include "pathfind/generated_config.hpp"
#include "pathfind/graph.hpp"
#include "pathfind/path.hpp"
#include "pathfind/priority_queue.hpp"

/**
 * Utility for printing total runtime memory usage.
 */

namespace {

std::string formatBytes(size_t bytes) {
  std::string value = std::to_string(bytes);

  for (int i = static_cast<int>(value.size()) - 3; i > 0; i -= 3) {
    value.insert(static_cast<size_t>(i), ",");
  }

  return value;
}

void printRow(const char* name, size_t bytes) {
  std::cout << "  " << std::left << std::setw(30) << name << std::right
            << std::setw(12) << formatBytes(bytes) << " B\n";
}

struct StaticMemory {
  size_t data;
  size_t bss;
};

StaticMemory getStaticMemory(const char* elf_path) {
  std::string command = "arm-none-eabi-size " + std::string(elf_path);

  FILE* pipe = popen(command.c_str(), "r");

  if (!pipe) {
    std::cerr << "Failed to run arm-none-eabi-size\n";
    return {0, 0};
  }

  char buffer[256];
  std::string output;

  while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
    output += buffer;
  }

  pclose(pipe);

  size_t newline = output.find('\n');

  if (newline == std::string::npos) {
    std::cerr << "Invalid size output\n";
    return {0, 0};
  }

  std::string values = output.substr(newline + 1);

  size_t text;
  size_t data;
  size_t bss;

  std::istringstream stream(values);

  stream >> text >> data >> bss;

  return {data, bss};
}

}  // namespace

int main(int argc, char* argv[]) {
  if (argc != 2) {
    std::cerr << "Usage: memory_report <firmware.elf>\n";
    return 1;
  }

  constexpr size_t graph_size = sizeof(pathfind::Graph);
  constexpr size_t astar_size = sizeof(pathfind::Astar);
  constexpr size_t path_size = sizeof(pathfind::Path);
  constexpr size_t priority_queue_size =
      sizeof(pathfind::PriorityQueue<pathfind::config::MAX_NODES_>);

  constexpr size_t fixed_total =
      graph_size + astar_size + path_size + priority_queue_size;

  const StaticMemory static_memory = getStaticMemory(argv[1]);
  const size_t static_total = static_memory.data + static_memory.bss;

  std::cout << "\n==============================================\n";
  std::cout << "                 MEMORY REPORT\n";
  std::cout << "==============================================\n\n";

  std::cout << "FIXED DOMAIN OBJECTS\n";

  printRow("Graph", graph_size);
  printRow("Astar", astar_size);
  printRow("Path", path_size);
  printRow("PriorityQueue", priority_queue_size);

  std::cout << "  ---------------------—----------------------\n";
  std::cout << "  " << std::left << std::setw(30) << "Total" << std::right
            << std::setw(12) << formatBytes(fixed_total) << " B\n";

  std::cout << "\n";

  std::cout << "STATIC MEMORY\n";

  printRow(".data", static_memory.data);
  printRow(".bss", static_memory.bss);

  std::cout << "  ---------------------—----------------------\n";
  std::cout << "  " << std::left << std::setw(30) << "Total" << std::right
            << std::setw(12) << formatBytes(static_total) << " B\n";

  std::cout << "\n";

  return 0;
}