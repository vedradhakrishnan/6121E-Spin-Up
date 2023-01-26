#include "main.h"

bool intake_state = false;

void intake_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      intake_control();
    }

    delay(10);
  }
}

void set_intake(int voltage) {
  intake = voltage;
  roller = voltage;
}

void intake_control() {
  if (controller.get_digital(DIGITAL_R1)) {
    set_intake(INTAKE_POWER);
  } else if (controller.get_digital(DIGITAL_R2)) {
    set_intake(OUTTAKE_POWER);
  } else
    set_intake(0);
}

void roller_auton() {
  intake.move_relative(ROLLER_POS, ROLLER_POWER);
}

void toggle_intake() {
  intake_state = !intake_state;
  set_intake(intake_state ? INTAKE_POWER : 0);
}
