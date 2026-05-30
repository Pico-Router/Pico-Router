#include <stdio.h>

#include "platform/uart.h"

void uart::write(std::string_view msg) {
  printf("%.*s", static_cast<int>(msg.size()), msg.data());
}