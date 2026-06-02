#include <iostream>

#include "platform/system_init.h"

pathfind::Astar System::router_;

void platform_init() { std::cout << "Initialized.\n"; }
