#include "pico/stdlib.h"
#include "platform/system_init.hpp"
#include "platform/uart.hpp"

pathfind::Astar System::router_;

void platform_init() { stdio_init_all(); }

void platform_sleep_ms(uint32_t ms) { sleep_ms(ms); };

void await_input() {
  uart::write("Press BOOTSEL button to continue...\n");
  platform_sleep_ms(1);
};
