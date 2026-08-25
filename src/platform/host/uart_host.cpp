#include <iostream>

#include "platform/uart.hpp"

void uart::write(std::string_view msg) { std::cout << msg << std::flush; }