#include <chrono>
#include <iostream>
#include <thread>

#include "platform/system_init.h"

pathfind::Astar System::router_;

void platform_init() {}

void platform_sleep_ms(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void await_input() {
  std::cout << "Press Enter to continue...\n";
  std::cin.get();
};