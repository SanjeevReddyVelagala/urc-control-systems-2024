#include "../include/implementation.hpp"
#include <../resource_list.hpp>
#include <cassert>
#include <cmath>
#include <cstdlib>
#include <libhal-arm-mcu/stm32f1/can.hpp>
#include <libhal-arm-mcu/stm32f1/can2.hpp>
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
  :  // m_drill(motor),
  m_clock(clock)
  , m_stepper_driver(step_motor_driver)
// , m_soil_sensor(soil_sensor)
{
}

// void drill_class::set_velocity()
// {

//   //***incorporate rotations per minute after testing

//   auto can_transceiver_ref = resources::can_transceiver();
//   auto clock_ref = resources::clock();
//   hal::can_message message = {
//     .id = 0x150,
//     .length = 8,
//     .payload = { 0xA2, 0x00, 0x00, 0x00, 0xE8, 0x03, 0x00, 0x00 }
//   };

//   can_transceiver_ref->send(message);
// }

void drill_class::set_stepper(long steps)
{
  m_stepper_driver.step(steps);
}

}  // namespace sjsu::drill
