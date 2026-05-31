#include <stdio.h>

#include <string_view>

#include "pico/stdlib.h"
#include "platform/uart.h"

using namespace uart;

void write(std::string_view msg) {
  printf("%.*s", static_cast<int>(msg.size()), msg.data());
}