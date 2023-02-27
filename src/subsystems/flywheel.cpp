#include <cmath>
#include "flywheel.hpp"
#include "globals.hpp"
#include "main.h"
#include "pros/rtos.hpp"

// double flywheel_target_vel = 0;
double flywheel_tbh = 0;
double flywheel_output = 0;
double flywheel_prev_error = 0;

// error = goal - currentSpeed;                // calculate the error;
// output += gain * error;                     // integrate the output;
// if (signbit(error)!= signbit(prev_error)) { // if zero crossing,
//   output = 0.5 * (output + tbh);            // then Take Back Half
//   tbh = output;                             // update Take Back Half variable
//   prev_error = error;                       // and save the previous error
// }


int power = 0;
int timer_f = 0;


void flywheel_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      flywheel_control();
    }

    set_flywheel_tbh();
    flywheel.move_velocity(flywheel_output);

    delay(10);
    timer_f += 10;
  }
}

// void set_flywheel_tbh(int velocity) {
//   flywheel_target_power = velocity;
//   flywheel_front.move_velocity(velocity);
// }

void set_flywheel(int voltage) {
  flywheel = voltage;
}

void set_flywheel_velocity(int v) {
  // flywheel.move_velocity(v);
  double flywheel_tbh = 0;
  double flywheel_output = FLYWHEEL_GAIN * v;
  double flywheel_prev_error = 0;
}

void set_flywheel_tbh() {
  int error = flywheel.get_target_velocity() - flywheel.get_actual_velocity();
  flywheel_output += FLYWHEEL_GAIN * error;

  if (flywheel_output > 600) flywheel_output = 600;
  if (flywheel_output < 0) flywheel_output = 0;

  if (signbit(error) != signbit(flywheel_prev_error)) {
    flywheel_output = 0.5 * (flywheel_tbh + flywheel_output);
    flywheel_tbh = flywheel_output;
  }

  flywheel_prev_error = error;
}

void flywheel_control() {
  if (timer_f > 150)
    if (controller.get_digital(DIGITAL_L1)) {
      timer_f = 0;
      // set_flywheel(FLYWHEEL_POWER_LOW);
      // power = power != FLYWHEEL_VEL_LOW ? FLYWHEEL_VEL_LOW : LOW;
      power = power != FLYWHEEL_POWER_LOW ? FLYWHEEL_POWER_LOW : LOW;
      delay(150);
    } else if (controller.get_digital(DIGITAL_L2)) {
      timer_f = 0;
      // set_flywheel(FLYWHEEL_POWER_HIGH);
      // power = power != FLYWHEEL_VEL_HIGH ? FLYWHEEL_VEL_HIGH : LOW;
      power = power != FLYWHEEL_POWER_HIGH ? FLYWHEEL_POWER_HIGH : LOW;
      delay(150);
    }

  // else
  //   set_flywheel(0);

  // set_flywheel_velocity(power);  
  set_flywheel(power);  
}
