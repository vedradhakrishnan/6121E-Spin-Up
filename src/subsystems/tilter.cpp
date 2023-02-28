#include "main.h"
#include "pros/rtos.hpp"

bool tilter_raised = LOW;

void toggle_tilter() {
  tilter_raised = !tilter_raised;
}

void tilter_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      if (controller.get_digital(DIGITAL_X)) tilter_raised = HIGH;
      if (controller.get_digital(DIGITAL_Y)) tilter_raised = LOW;
    }

    tilter.set_value(tilter_raised);
    delay(10);
  }
}
