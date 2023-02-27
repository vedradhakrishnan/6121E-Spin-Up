
#include "main.h"
#include "pros/rtos.hpp"

bool auton_first = true;
bool driver_first = true;

void chassis_task(void *parameter) {
  // while (true) {

  //   if (!competition::is_autonomous()) {
  //     if (driver_first) {
  //       chassis.set_drive_brake(MOTOR_BRAKE_COAST);
  //       driver_first = false;
  //     }
  //     chassis.tank(); // Tank control
  //   }

  //   delay(10);
  // }
}