#include "globals.hpp"
#include "main.h"
#include "pros/rtos.hpp"

// double flywheel_target_power = 0;
// double flywheel_tbh;
// double flywheel_output;
// double flywheel_prev_error;

int power = 0;
int timer_f = 0;


void flywheel_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      flywheel_control();
    }

    delay(10);
    timer_f += 10;
  }
}

void set_flywheel(int voltage) {
  flywheel_front = voltage;
  flywheel_back = voltage;
}

void flywheel_control() {
  if (timer_f > 150)
    if (controller.get_digital(DIGITAL_L1)) {
      timer_f = 0;
      // set_flywheel(FLYWHEEL_POWER_LOW);
      power = power != FLYWHEEL_POWER_LOW ? FLYWHEEL_POWER_LOW : LOW;
      delay(150);
    } else if (controller.get_digital(DIGITAL_L2)) {
      timer_f = 0;
      // set_flywheel(FLYWHEEL_POWER_HIGH);
      power = power != FLYWHEEL_POWER_HIGH ? FLYWHEEL_POWER_HIGH : LOW;
      delay(150);
    }

  // else
  //   set_flywheel(0);

  set_flywheel(power);  
}
