#include <libhal-arm-mcu/stm32f1/input_pin.hpp>
#include <libhal-arm-mcu/stm32f1/output_pin.hpp>
#include <ultrasonic_sensor_hcsr04.hpp>

using namespace std::chrono_literals;

namespace sjsu::drivers {
hcsr04::hcsr04(ctor_params& p_params)
  : m_trigger(p_params.trigger_pin)
  , m_echo(p_params.echo_pin)
  , m_clock(p_params.clock)
{
}

float hcsr04::get_distance()
{
  m_trigger->level(true);
  hal::delay(*m_clock, 10us);
  m_trigger->level(false);

  while (m_echo->level() == true) {
  }

  auto start = m_clock->uptime();

  while (m_echo->level() == false) {
  }

  auto end = m_clock->uptime();

  auto echo_duration_ticks = end - start;

  auto frequency = m_clock->frequency();

  auto echo_duration_microseconds = (echo_duration_ticks / frequency) * 1000000;

  // 58microseconds = 1cm of measured distance
  float distance = echo_duration_microseconds / 58;

  return distance;
}

}  // namespace sjsu::drivers
