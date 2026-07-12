#pragma once
#include <libhal-arm-mcu/stm32f1/input_pin.hpp>
#include <libhal-arm-mcu/stm32f1/output_pin.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/pointers.hpp>

using namespace std::chrono_literals;
using namespace hal::literals;

namespace sjsu::drivers {
class hcsr04
{
public:
  struct ctor_params
  {
    hal::v5::strong_ptr<hal::output_pin> trigger_pin;
    hal::v5::strong_ptr<hal::input_pin> echo_pin;
    hal::v5::strong_ptr<hal::steady_clock> clock;
  };

  hcsr04(ctor_params& p_params);

private:
  hal::v5::strong_ptr<hal::output_pin> m_trigger;
  hal::v5::strong_ptr<hal::input_pin> m_echo;
  hal::v5::strong_ptr<hal::steady_clock> m_clock;
}
}  // namespace sjsu::drivers
