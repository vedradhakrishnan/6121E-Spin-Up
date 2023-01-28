#include "main.h"
#include "pros/rtos.hpp"

int driver_time = 0;

void expansion_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      if (controller.get_digital(DIGITAL_UP)) {
        expansion.set_value(HIGH);
        delay(INDEXER_ENGAGE_TIME);
        expansion.set_value(LOW);
        // expansion.set_value(driver_time > CONTROL_TIME - EXPANSION_TIME);
      }

      driver_time += 10;
    }

    delay(10);
  }
}
