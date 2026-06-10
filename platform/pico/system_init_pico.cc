#include "pico/stdlib.h"
#include "platform/system_init.h"
#include "platform/uart.h"

pathfind::Astar System::router_;

void platform_init() { stdio_init_all(); }

void platform_sleep_ms(uint32_t ms) { sleep_ms(ms); };

void await_input() {
  uart::write("Press BOOTSEL button to continue...\n");

  while (!get_bootsel_button()) {
    platform_sleep_ms(1);
  }

  while (get_bootsel_button()) {
    platform_sleep_ms(1);
  }
};

namespace {

// AI generated code
bool __no_inline_not_in_flash_func(get_bootsel_button)() {
  const uint cs_pin_index = 1;

  // Disable interrupts while flash access is temporarily altered.
  uint32_t flags = save_and_disable_interrupts();

  // Put flash CS into Hi-Z so we can observe the BOOTSEL state.
  hw_write_masked(&ioqspi_hw->io[cs_pin_index].ctrl,
                  GPIO_OVERRIDE_LOW << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                  IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

  // Give the signal a moment to settle.
  for (volatile int i = 0; i < 1000; ++i) {
  }

#if defined(_ARM_ARCH_6M_)
  const uint32_t cs_bit = 1u << 1;
#else
  const uint32_t cs_bit = SIO_GPIO_HI_IN_QSPI_CSN_BITS;
#endif
  bool button_state = (sio_hw->gpio_hi_in & cs_bit) != 0;

  // Restore normal flash CS handling before returning to flash code.
  hw_write_masked(&ioqspi_hw->io[cs_pin_index].ctrl,
                  GPIO_OVERRIDE_NORMAL << IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_LSB,
                  IO_QSPI_GPIO_QSPI_SS_CTRL_OEOVER_BITS);

  restore_interrupts(flags);
  return button_state;
}

}  // namespace