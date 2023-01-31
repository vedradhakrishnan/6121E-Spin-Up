#include "main.h"

// double flywheel_target_power = 0;
// double flywheel_tbh;
// double flywheel_output;
// double flywheel_prev_error;




void flywheel_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      flywheel_control();
    }

    delay(10);
  }
}

void set_flywheel(int voltage) {
  flywheel_front = voltage;
  flywheel_back = voltage;
}

void flywheel_control() {
  if (controller.get_digital(DIGITAL_L1)) {
    set_flywheel(FLYWHEEL_POWER_LOW);
  } else if (controller.get_digital(DIGITAL_L2)) {
    set_flywheel(FLYWHEEL_POWER_HIGH);
  } else
    set_flywheel(0);
}
