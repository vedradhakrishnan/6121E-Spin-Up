#include "chassis.hpp"
#include "display/lv_core/lv_lang.h"
#include "globals.hpp"
#include "main.h"
#include <cmath>
#include <cstdlib>

//ODOM VARS
double chassis_x = 0.0;
double chassis_z = 0.0;
double chassis_theta = 0.0;

double last_imu1 = 0.0;
double last_imu2 = 0.0;
double new_imu1 = 0.0;
double new_imu2 = 0.0;

double target_x;
double target_z;
double target_theta;

//PID VARS
double trans_error;
double trans_sum;
double trans_last;

double rot_error;
double rot_sum;
double rot_last;

int max_power;

//Pid ==> slew function variables
double last_right = 0.0;
double last_left = 0.0;
double pid_left;
double pid_right;
double tank_left;
double tank_right;
double slewed_right;
double slewed_left;

/* TENTATIVE FLOW
auton: 2 drives, pid + brake
control: tank drive + pid

for slew: first check chassis mode
if pid, then  use pid voltage as inp,
if arcade, use some sort of output?

or have slew function take 2 inputs--sorta jank

always set right and left to slewed voltage no matter stage
*/

int brake_timer = 0;
int chassis_mode = DRIVE_PID;

//HELPERS
double tracker_inches(int ticks) {
  return (TRACKING_DIAM * M_PI) * (ticks / 360.0);
}

void initialize_aps(double x_i, double z_i, double theta_i) {
  chassis_x = x_i;
  chassis_z = z_i;
  chassis_theta = theta_i;
}


void chassis_lock() {
  drive_bl.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  drive_fl.set_brake_mode(E_MOTOR_BRAKE_HOLD);

  drive_br.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_HOLD);
  drive_fr.set_brake_mode(E_MOTOR_BRAKE_HOLD);
}

void chassis_unlock() {
  drive_fr.set_brake_mode(E_MOTOR_BRAKE_COAST);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_COAST);
  drive_fl.set_brake_mode(E_MOTOR_BRAKE_COAST);

  drive_br.set_brake_mode(E_MOTOR_BRAKE_COAST);
  // drive_lc.set_brake_mode(E_MOTOR_BRAKE_COAST);
  drive_fr.set_brake_mode(E_MOTOR_BRAKE_COAST);
}

void set_chassis(int left, int right) {
  drive_bl = left;
  // drive_lc = left;
  drive_fl = left;

  drive_br = right;
  // drive_lc = left;
  drive_fr = right;
}

double encoder_inches(int ticks) {
  return ticks * (M_PI / 450.0) * 3.25;
}

void gyrodom_update_aps() {
  double left = tracker_inches(odom_left.get_value());
  odom_left.reset();

  double right = tracker_inches(odom_right.get_value());
  odom_right.reset();

  double center = tracker_inches(odom_center.get_value());
  odom_center.reset();

  double delta_theta = (left - right) / TRACKING_WIDTH;
  double average_theta = chassis_theta + (delta_theta / 2);
  // chassis_theta += delta_theta;

  double local_x; double local_z;
  if (delta_theta == 0.0) {
    local_x = center;
    local_z = right;
  } else {
    local_x = 2 * sin(delta_theta / 2) * ((center / delta_theta) + TRACKING_WIDTH / 2);
    local_z = 2 * sin(delta_theta / 2) * ((right / delta_theta) + TRACKING_WIDTH / 2);
  }

  double local_r; double local_theta;
  if (local_x == 0) {
    local_r = local_z;
    local_theta = M_PI_2;
  } else {
    local_r = sgn(local_x) * sqrt(local_x * local_x + local_z * local_z); //Distance formula to convert para to polar, times signum of localX
    local_theta = atan(local_z / local_x);
  }
  local_theta -= average_theta;

  //UPDATE CHASSIS POSITION
  chassis_x += local_r * cos(local_theta);
  chassis_z += local_r * sin(local_theta);

  if (!imu1.is_calibrating() && !imu2.is_calibrating()) {
    new_imu1 = imu1.get_heading() * (M_PI / 180);
    new_imu2 = imu2.get_heading() * (M_PI / 180);

    double delta_imu1 = new_imu1 - last_imu1;
    double delta_imu2 = new_imu2 - last_imu2;

    if (delta_imu1 > M_PI)
      delta_imu1 -= 2 * M_PI;
    else if (delta_imu1 < -M_PI)
      delta_imu1 += 2 * M_PI;

    if (delta_imu2 > M_PI)
      delta_imu2 -= 2 * M_PI;
    else if (delta_imu2 < -M_PI)
      delta_imu2 += 2 * M_PI;

    // lcd::set_text(1, "X: " + std::to_string(int(100 * delta_imu1) / 100.0));
    // lcd::set_text(2, "Z: " + std::to_string(int(100 * new_imu1) / 100.0));
    // lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));

    chassis_theta += 0.5 * (delta_imu1 + delta_imu2);
    last_imu1 = new_imu1;
    last_imu2 = new_imu2; 
  }

}

void imu_update_aps() {


  double left = encoder_inches(drive_bl.get_position() + drive_fl.get_position()) / 2.0;
  drive_bl.tare_position();
  drive_fl.tare_position();

  double right = encoder_inches(drive_br.get_position() + drive_fl.get_position()) / 2.0;
  drive_br.tare_position();
  drive_fr.tare_position();
  
  // double delta_theta = (left - right) / CHASSIS_WIDTH;
  // double arc_r = 0.5 * (left + right) / delta_theta;

  // double local_r; double local_theta;
  // local_theta = 0.5 * delta_theta;
  // local_r = 2 * arc_r * sin(local_theta);
  // local_theta -= chassis_theta;

  // double local_x; double local_z;
  // local_x = -arc_r * cos(delta_theta) * sin(delta_theta);
  // local_z = -arc_r * sin(delta_theta) * sin(delta_theta);

  
  // lcd::set_text(1, "X: " + std::to_string(int(100 * local_r) / 100.0));
  // lcd::set_text(2, "Z: " + std::to_string((100 * delta_theta)));
  // lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));

  // double local_r; double local_theta;
  // // local_r = -arc_r * sin(delta_theta);
  // if (local_x == 0) {
  //   local_r = local_z;
  //   local_theta = M_PI_2;
  // } else {
  //   local_r = sgn(local_x) * sqrt(local_x * local_x + local_z * local_z); //Distance formula to convert para to polar, times signum of localX
  //   local_theta = atan(local_z / local_x);
  // }
  // local_theta -= chassis_theta;
  //chassis_x = chassis_x + local_r * cos(local_theta);
  double delta_theta = (left - right) / CHASSIS_WIDTH;
  if (delta_theta != 0.0) {
    double arc_r = 0.5 * (left + right) / delta_theta;

    double local_r; double local_theta;
    local_theta = 0.5 * delta_theta;
    local_r = 2 * arc_r * sin(local_theta);
    local_theta -= chassis_theta;

    chassis_x += local_r * cos(local_theta);
    chassis_z += local_r * sin(local_theta);
    // lcd::set_text(1, "X: " + std::to_string(chassis_x));
    // lcd::set_text(2, "Z: " + std::to_string(local_r * cos(local_theta)));
    // lcd::set_text(3, "theta: " + std::to_string(arc_r));
  }



  //ok
  if (imu1.is_calibrating() || imu2.is_calibrating())
    // chassis_theta = (imu1.get_heading() + imu2.get_heading()) * (M_PI / 360.0);
    chassis_theta = 0.0;
  else {
    new_imu1 = imu1.get_heading() * (M_PI / 180);
    new_imu2 = imu2.get_heading() * (M_PI / 180);

    double delta_imu1 = new_imu1 - last_imu1;
    double delta_imu2 = new_imu2 - last_imu2;

    if (delta_imu1 > M_PI)
      delta_imu1 -= 2 * M_PI;
    else if (delta_imu1 < -M_PI)
      delta_imu1 += 2 * M_PI;

    if (delta_imu2 > M_PI)
      delta_imu2 -= 2 * M_PI;
    else if (delta_imu2 < -M_PI)
      delta_imu2 += 2 * M_PI;

    // lcd::set_text(1, "X: " + std::to_string(int(100 * delta_imu1) / 100.0));
    // lcd::set_text(2, "Z: " + std::to_string(int(100 * new_imu1) / 100.0));
    // lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));

    chassis_theta += 0.5 * (delta_imu1 + delta_imu2);
    last_imu1 = new_imu1;
    last_imu2 = new_imu2; 
  }

}

void odom_update_aps() {
  //CHANGE IN ENCODER VALUES FOR TRACKING WHEELS
  //also resets the encoders so that we can find the change in the rotational encoder values from the next cycle
  double left = tracker_inches(odom_left.get_value());
  odom_left.reset();

  double right = tracker_inches(odom_right.get_value());
  odom_right.reset();

  double center = tracker_inches(odom_center.get_value());
  odom_center.reset();

  double delta_theta = (left - right) / TRACKING_WIDTH;
  double average_theta = chassis_theta + (delta_theta / 2);
  chassis_theta += delta_theta;

  double local_x; double local_z;
  if (delta_theta == 0.0) {
    local_x = center;
    local_z = right;
  } else {
    local_x = 2 * sin(delta_theta / 2) * ((center / delta_theta) + TRACKING_WIDTH / 2);
    local_z = 2 * sin(delta_theta / 2) * ((right / delta_theta) + TRACKING_WIDTH / 2);
  }

  double local_r; double local_theta;
  if (local_x == 0) {
    local_r = local_z;
    local_theta = M_PI_2;
  } else {
    local_r = sgn(local_x) * sqrt(local_x * local_x + local_z * local_z); //Distance formula to convert para to polar, times signum of localX
    local_theta = atan(local_z / local_x);
  }
  local_theta -= average_theta;

  //UPDATE CHASSIS POSITION
  chassis_x += local_r * cos(local_theta);
  chassis_z += local_r * sin(local_theta);


  
}


//constant drive algorithm
// void straight_const(double inches, int power) {
//   chassis_mode = DRIVE_CONST;

//   target_x = chassis_x + inches * cos(chassis_theta);
//   target_z = chassis_z + inches * sin(chassis_theta);
//   target_theta = chassis_theta;

//   max_power = power;
// }

//this sets the target that the robot must travel to (power represents the maximum voltage)
void straight_pid(double inches, int power) {
  chassis_mode = DRIVE_PID;

  target_x = chassis_x + inches * sin(chassis_theta);
  target_z = chassis_z + inches * cos(chassis_theta);
  target_theta = chassis_theta;

  double x_error = target_x - chassis_x;
  double z_error = target_z - chassis_z;

  trans_error = sqrt(pow(x_error, 2) + pow(z_error, 2));
  trans_last = trans_error;
  rot_error = target_theta - chassis_theta;  
  trans_sum = 0;
  rot_sum = 0;
  rot_last = rot_error;

  max_power = power;
}

void turn_pid(double degrees, int power) {
  chassis_mode = DRIVE_PID;

  target_x = chassis_x;
  target_z = chassis_z;
  target_theta = chassis_theta + degrees * (M_PI / 180);

  double x_error = target_x - chassis_x;
  double z_error = target_z - chassis_z;

  trans_error = sqrt(pow(x_error, 2) + pow(z_error, 2));
  trans_last = trans_error;
  rot_error = target_theta - chassis_theta;  
  trans_sum = 0;
  rot_sum = 0;
  rot_last = rot_error;

  max_power = power;
}

void drive_brake() {
	chassis_mode = DRIVE_BRAKE;
	brake_timer = 0;
}

void tank_drive() {
  int left_stick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
  int right_stick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

  if(abs(left_stick) < 10) left_stick = 0;
  if(abs(right_stick) < 10) right_stick = 0;

  // lcd::set_text(4, "left: " + std::to_string(left_stick));
  // lcd::set_text(5, "right: " + std::to_string(right_stick));

  // set_chassis(left_stick, right_stick);
  tank_left = -right_stick;
  tank_right = -left_stick;
}


void slew_power() {
  double left_in;
  double right_in;
  if (chassis_mode == DRIVE_PID) {
    left_in = pid_left;
    right_in = pid_right;
  } else if (chassis_mode == DRIVE_TANK) {
    left_in = tank_left;
    right_in = tank_right;
    max_power = 127;
  } else if (chassis_mode == DRIVE_BRAKE) {
    left_in = 0;
    right_in = 0;
    max_power = 127;
  }

  lcd::set_text(4, "left: " + std::to_string(left_in));
  lcd::set_text(5, "right: " + std::to_string(right_in));

  //left side
  int v_dir_left = last_left != 0 ? sgn(last_left) : sgn(left_in);
  int a_dir_left = last_left != left_in ? v_dir_left * sgn(left_in - last_left) : 0;

  int left_limit = a_dir_left >= 0 ? MAX_ACCEL_SLEW : MAX_DECEL_SLEW;
  double delta_left = a_dir_left * v_dir_left * (fabs(left_in - last_left) < left_limit ? fabs(left_in - last_left) : left_limit);

  slewed_left = last_left + delta_left;
  if (fabs(slewed_left) > max_power) 
    slewed_left = sgn(slewed_left) * max_power;

  //right side
  int v_dir_right = last_right != 0 ? sgn(last_right) : sgn(right_in);
  int a_dir_right = last_right != right_in ? v_dir_right * sgn(right_in - last_right) : 0;

  int right_limit = a_dir_right >= 0 ? MAX_ACCEL_SLEW : MAX_DECEL_SLEW;
  double delta_right = a_dir_right * v_dir_right * (fabs(right_in - last_right) < right_limit ? fabs(right_in - last_right) : right_limit);

  slewed_right = last_right + delta_right;

  // lcd::set_text(6, "sleft: " + std::to_string(slewed_right));
  // lcd::set_text(7, "sright: " + std::to_string(slewed_left));

  if (fabs(slewed_right) > max_power)
    slewed_right = sgn(slewed_right) * max_power;
}

int sgn(double num) {
  return num < 0 ? -1 : 1;
}

//concerned with setting the voltage during the autonomous based on the error that the robot has relative to the target. updates the voltage every cycle
void chassis_auton() {

  // odom_update();
	// controller.set_text(1, 0, "X: " + std::to_string(chassis_x) + " Z: " + std::to_string(chassis_z));
  // controller.set_text(1, 1, "theta: " + std::to_string(chassis_theta));


  if (chassis_mode == DRIVE_PID) {
    double x_error = target_x - chassis_x;
    double z_error = target_z - chassis_z;
    trans_error = sqrt(pow(x_error, 2) + pow(z_error, 2));
    rot_error = target_theta - chassis_theta;

    double dot_product = x_error * sin(chassis_theta) + z_error * cos(chassis_theta);
    int trans_dir = sgn(dot_product);

    double turn;
    double power;
    if (fabs(rot_error) < MIN_TURN) {
      double p_turn = SLANT_KP * rot_error;
      double i_turn = SLANT_KI * rot_sum;
      double d_turn = SLANT_KD * sgn(rot_error) * (rot_error - rot_last);
      turn = p_turn + i_turn + d_turn;

      double p_power = STRAIGHT_KP * trans_error;
      double i_power = STRAIGHT_KI * trans_sum;
      double d_power = STRAIGHT_KD * trans_dir * (trans_error - trans_last);
      power = p_power + i_power + d_power;

    } else {
      double p_turn = TURN_KP * rot_error;
      double i_turn = TURN_KI * rot_sum;
      double d_turn = TURN_KD * sgn(rot_error) * (rot_error - rot_last);
      
      turn = p_turn + i_turn + d_turn;

      power = 0;
    }

    lcd::set_text(6, "trans: " + std::to_string(trans_error));
    lcd::set_text(7, "rot: " + std::to_string(rot_error));
    // set_chassis(power + turn, power - turn);
    pid_left = (trans_dir * power + turn);
    pid_right = (trans_dir * power - turn);

    trans_last = trans_error;
    trans_sum += trans_error;
    rot_last = rot_error;
    rot_sum += rot_error;

    if (fabs(trans_error) < MIN_TRANS_ERROR && fabs(rot_error) < MIN_ROT_ERROR) {
      drive_brake();
    }
  } else if (chassis_mode == DRIVE_BRAKE) {
    brake_timer += 10;
  }

}

void chassis_task(void *parameter) {
  int time = 0;

  while (true) {
    // odom_update_aps();
    // imu_update_aps();
    gyrodom_update_aps();


    if (!competition::is_autonomous()) {
      chassis_mode = DRIVE_TANK; //comment out later
      tank_drive();
      // set_chassis(tank_left, tank_right);
    } else {
      //odom_update();
      chassis_auton();
      // display time elapsed, odom coords, and PID vars
    }

    slew_power();
    set_chassis(slewed_left, slewed_right);
    last_left = slewed_left;
    last_right = slewed_right;

    lcd::set_text_color(255, 0, 0);
    lcd::set_text(0, "TIME: " + std::to_string(time));
    // // lcd::set_text_color(0, 0, 255);
    lcd::set_text(1, "X: " + std::to_string(int(100 * chassis_x) / 100.0));
    lcd::set_text(2, "Z: " + std::to_string(int(100 * chassis_z) / 100.0));
    lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));
    // lcd::set_text(3, "theta: " + std::to_string(chassis_theta));

    time += 10;
    delay(10);
  }
}
