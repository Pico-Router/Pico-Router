#include <stdio.hpp>

#include <string_view>

#include "pico/stdlib.hpp"
#include "platform/uart.hpp"

void uart::write(std::string_view msg) {
  printf("%.*s", static_cast<int>(msg.size()), msg.data());
}