#include "main.h"
#include "pros/rtos.hpp"

bool auton_first = true;
bool driver_first = true;


// void set_chassis(int left, int right) {
//   drive_bl = left;
//   drive_lc = left;
//   drive_fl = left;

//   drive_br = right;
//   drive_lc = left;
//   drive_fr = right;
// }

// void tank_drive() {
//   int left_stick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
//   int right_stick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

//   if(abs(left_stick) < 10) left_stick = 0;
//   if(abs(right_stick) < 10) right_stick = 0;

//   // lcd::set_text(4, "left: " + std::to_string(left_stick));
//   // lcd::set_text(5, "right: " + std::to_string(right_stick));

//   // set_chassis(left_stick, right_stick);
//   tank_left = -right_stick;
//   tank_right = -left_stick;
// }


// void slew_power() {
//   double left_in;
//   double right_in;
//   if (chassis_mode == DRIVE_PID) {
//     left_in = pid_left;
//     right_in = pid_right;
//   } else if (chassis_mode == DRIVE_TANK) {
//     left_in = tank_left;
//     right_in = tank_right;
//     max_power = 127;
//   } else if (chassis_mode == DRIVE_BRAKE) {
//     left_in = 0;
//     right_in = 0;
//     max_power = 127;
//   }

//   lcd::set_text(4, "left: " + std::to_string(left_in));
//   lcd::set_text(5, "right: " + std::to_string(right_in));

//   //left side
//   int v_dir_left = last_left != 0 ? sgn(last_left) : sgn(left_in);
//   int a_dir_left = last_left != left_in ? v_dir_left * sgn(left_in - last_left) : 0;

//   int left_limit = a_dir_left >= 0 ? MAX_ACCEL_SLEW : MAX_DECEL_SLEW;
//   double delta_left = a_dir_left * v_dir_left * (fabs(left_in - last_left) < left_limit ? fabs(left_in - last_left) : left_limit);

//   slewed_left = last_left + delta_left;
//   if (fabs(slewed_left) > max_power) 
//     slewed_left = sgn(slewed_left) * max_power;

//   //right side
//   int v_dir_right = last_right != 0 ? sgn(last_right) : sgn(right_in);
//   int a_dir_right = last_right != right_in ? v_dir_right * sgn(right_in - last_right) : 0;

//   int right_limit = a_dir_right >= 0 ? MAX_ACCEL_SLEW : MAX_DECEL_SLEW;
//   double delta_right = a_dir_right * v_dir_right * (fabs(right_in - last_right) < right_limit ? fabs(right_in - last_right) : right_limit);

//   slewed_right = last_right + delta_right;

//   // lcd::set_text(6, "sleft: " + std::to_string(slewed_right));
//   // lcd::set_text(7, "sright: " + std::to_string(slewed_left));

//   if (fabs(slewed_right) > max_power)
//     slewed_right = sgn(slewed_right) * max_power;
// }

int sgn(double num) {
  return num < 0 ? -1 : 1;
}

void chassis_task(void *parameter) {
  // int time = 0;

  // while (true) {
  //   // odom_update_aps();
  //   // imu_update_aps();
  //   // gyrodom_update_aps();


  //   if (!competition::is_autonomous()) {
  //     chassis_mode = DRIVE_TANK; //comment out later
  //     tank_drive();
  //     // set_chassis(tank_left, tank_right);
  //   } else {
  //     //odom_update();
  //     chassis_auton();
  //     // display time elapsed, odom coords, and PID vars
  //   }

  //   slew_power();
  //   set_chassis(slewed_left, slewed_right);
  //   last_left = slewed_left;
  //   last_right = slewed_right;

  //   lcd::set_text_color(255, 0, 0);
  //   lcd::set_text(0, "TIME: " + std::to_string(time));
  //   // // lcd::set_text_color(0, 0, 255);
  //   lcd::set_text(1, "X: " + std::to_string(int(100 * chassis_x) / 100.0));
  //   lcd::set_text(2, "Z: " + std::to_string(int(100 * chassis_z) / 100.0));
  //   lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));
  //   // lcd::set_text(3, "theta: " + std::to_string(chassis_theta));

  //   time += 10;
  //   delay(10);
  // }
}
