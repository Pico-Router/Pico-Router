#include <chrono>
#include <iostream>
#include <thread>

#include "platform/system_init.h"

pathfind::Astar System::router_;

void platform_init() { std::cout << "Initialized.\n"; }

void platform_sleep_ms(uint32_t ms) {
  std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}