#include <iostream>

#include "platform/uart.h"

void uart::write(std::string_view msg) { std::cout << msg << std::flush; }