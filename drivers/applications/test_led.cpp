#include <libhal-util/serial.hpp>
#include <libhal-util/steady_clock.hpp>
#include <libhal/error.hpp>
#include <libhal/pointers.hpp>
#include <libhal/units.hpp>
#include "../hardware_map.hpp"
#include <drv8825.hpp>

using namespace hal::literals;
using namespace std::chrono_literals;

namespace sjsu::drivers {

void application()
{
  auto clock = resources::clock();
  auto terminal = resources::console();
        hal::print(*terminal, "starting\n");

try{
  auto dir_pin = resources::output_pin_5();
  auto step_pin = resources::output_pin_4();
  auto m1_pin = resources::output_pin_0();
  auto m2_pin = resources::output_pin_6();
  auto m3_pin = resources::output_pin_7();

    while (true) {

        m3_pin->level(true);
        hal::print(*terminal, "high\n");
        hal::delay(*clock, 5000ms);
        m3_pin->level(false);
        hal::print(*terminal, "low\n");
        hal::delay(*clock, 5000ms);    
  }
}catch(hal::exception const& e){
  hal::print(*terminal, "error caught\n");
}
}

}