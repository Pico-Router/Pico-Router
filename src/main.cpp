#include "platform/system_init.hpp"
#include "platform/uart.hpp"

int main() {
  platform_init();
  System global_system;

  // await_input();

  // while (true) {
  //   platform_sleep_ms(1000);
  //   uart::write("Hello World!\n");
  // };
  return 0;
}