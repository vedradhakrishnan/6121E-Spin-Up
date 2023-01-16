#include "main.h"

void expansion_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      if (controller.get_digital(DIGITAL_UP)) {
        expansion_left.set_value(HIGH);
      }
    }

    delay(10);
  }
}
