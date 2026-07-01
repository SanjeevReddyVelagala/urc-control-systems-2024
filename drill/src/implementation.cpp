#include "../include/implementation.hpp"
#include <../resource_list.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/error.hpp>
#include <libhal/pointers.hpp>
#include <libhal/units.hpp>

using namespace std::chrono_literals;
using namespace hal::literals;

namespace sjsu::drill {

drill_class::drill_class(
  // hal::v5::strong_ptr<hal::actuator::rmd_mc_x_v2> motor,
  hal::v5::strong_ptr<hal::steady_clock> clock,
  sjsu::drivers::drv8825 step_motor_driver
  // , sjsu::drivers::sht21 soil_sensor
  )
  :  // m_drill(motor)
  m_clock(clock)
  , m_stepper_driver(step_motor_driver)
// , m_soil_sensor(soil_sensor)
{
}

// void drill_class::stop()
// {
//   m_drill->velocity_control(0);
// }

// void drill_class::set_velocity(int rpm)
// {
//   m_drill->velocity_control(rpm);
// }
}  // namespace sjsu::drill