#include "pico/stdlib.h"
#include "platform/system_init.h"

pathfind::Astar System::router_;

void platform_init() { stdio_init_all(); }
