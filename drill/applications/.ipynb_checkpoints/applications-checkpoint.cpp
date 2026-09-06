
#include "../../drivers/include/drv8825.hpp"
#include "../../drivers/include/soil_sensor_sht21.hpp"
#include "implementation.hpp"
#include <../resource_list.hpp>
#include <exception>
#include <libhal-actuator/smart_servo/rmd/mc_x_v2.hpp>
#include <libhal-exceptions/control.hpp>
#include <libhal-util/bit_bang_i2c.hpp>
#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/can.hpp>
#include <libhal/error.hpp>
#include <libhal/pointers.hpp>
#include <libhal/units.hpp>
#include <memory_resource>
using namespace hal::literals;
using namespace std::chrono_literals;

namespace sjsu::drill {
void application()
{
  auto terminal = resources::console();
  hal::print(*terminal, "Terminal Initialized...\n\n");
  try {
    auto clock = resources::clock();
    hal::print(*terminal, "Clock...\n\n");

    auto dir_pin = resources::dir_pin();
    hal::print(*terminal, " dir pin \n");
    auto step_pin = resources::step_pin();
    hal::print(*terminal, "step pin \n");
    auto m1_pin = resources::m1_pin();
    hal::print(*terminal, " m1 pin \n");
    auto m2_pin = resources::m2_pin();
    hal::print(*terminal, " m2 pin \n");

    auto m0_pin = resources::m0_pin();
    hal::print(*terminal, " m0 pin \n");

    auto enbl = resources::enbl();
    hal::print(*terminal, " enbl \n");

    auto fault = resources::fault();
    hal::print(*terminal, "fault \n");

    enbl->level(0);
    hal::print(*terminal, "Initazin Cna bus Manager \n\n");
    auto manager = resources::can_bus_manager();
    hal::print(*terminal, "Bus Manager Initialized ...\n\n");
    auto transceiver = resources::can_transceiver();
    hal::print(*terminal, "Transceiver Initialized ...\n\n");

    sjsu::drivers::drv8825 stepper_controller(
      sjsu::drivers::drv8825::ctor_params{
        .direction_pin = dir_pin,
        .step_pin = step_pin,
        .steady_clock = clock,
        .motor_step_factor = sjsu::drivers::drv8825::step_factor::one,
        .full_steps_per_rotation = 2048,
        .step_half_period = 450us,
        .mode_pins = { m0_pin, m1_pin, m2_pin },
      });

    hal::print(*terminal, "Stepper Motor Initialized\n\n");

    manager->filter_mode(hal::can_bus_manager::accept::all);
    manager->bus_on();

    hal::print(*terminal, "Motor Initialized...\n\n");

    // auto i2c = resources::i2c();
    // hal::print(*terminal, "I2c...\n\n");

    // sjsu::drivers::sht21 m_sht21 = sjsu::drivers::sht21(i2c);

    drill_class drill(
      // resources::drill_motor(),
      clock,
      stepper_controller);  // add , m_sht21 when i2c works

    while (true) {
      // drill.set_velocity();
      drill.set_stepper(2400);
      hal::print<64>(*terminal, "dir level going up: %d\n", dir_pin->level());
      hal::print<64>(*terminal, "fault level: %d\n", fault->level());
      hal::delay(*clock, 5000ms);
      drill.set_stepper(-2400);
      hal::print<64>(*terminal, "dir level going down: %d\n", dir_pin->level());
      hal::print<64>(*terminal, "fault level: %d\n", fault->level());
      hal::delay(*clock, 5000ms);
    }
  }

  catch (hal::exception e) {
    hal::print<50>(*terminal, "%d \n", e.error_code());
    hal::print(*terminal, "something died\n");
  }
}
}  // namespace sjsu::drill
