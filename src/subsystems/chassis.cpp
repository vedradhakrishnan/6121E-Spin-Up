#include "main.h"

//ODOM VARS
double chassis_x = 0.0;
double chassis_z = 0.0;
double chassis_theta = 0.0;

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

int brake_timer = 0;
int chassis_mode = DRIVE_CONST;

//HELPERS
double tracker_inches(int ticks) {
  return (TRACKING_DIAM * M_PI) * (ticks / 360.0);
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

void odom_update() {
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
    local_r = (fabs(local_x) / local_x) * sqrt(local_x * local_x + local_z * local_z); //Distance formula to convert para to polar, times signum of localX
    local_theta = atan(local_z / local_x);
  }
  local_theta -= average_theta;

  //UPDATE CHASSIS POSITION
  chassis_x += local_r * cos(local_theta);
  chassis_z += local_r * sin(local_theta);
}


//constant drive algorithm
void straight_const(double inches, int power) {
  chassis_mode = DRIVE_CONST;

  target_x = chassis_x + inches * cos(chassis_theta);
  target_z = chassis_z + inches * sin(chassis_theta);
  target_theta = chassis_theta;

  max_power = power;
}

//this sets the target that the robot must travel to (power represents the maximum voltage)
void straight_pid(double inches, int power) {
  chassis_mode = DRIVE_PID;

  target_x = chassis_x + inches * cos(chassis_theta);
  target_z = chassis_z + inches * sin(chassis_theta);
  target_theta = chassis_theta;

  double x_error = target_x - chassis_x;
  double z_error = target_z - chassis_z;

  trans_error = sqrt(pow(x_error, 2) + pow(z_error, 2));
  trans_last = trans_error;
  rot_error = target_theta - chassis_theta;  trans_sum = 0;
  rot_sum = 0;
  rot_last = rot_error;

  max_power = power;
}

void turn_const(double degrees, int power) {
  chassis_mode = DRIVE_CONST;

  target_x = chassis_x;
  target_z = chassis_z;
  target_theta = chassis_theta + degrees * (M_PI / 180);

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

  lcd::set_text(4, "left: " + std::to_string(left_stick));
  lcd::set_text(5, "right: " + std::to_string(right_stick));

  set_chassis(left_stick, right_stick);
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

    double turn;
    double power;
    if (fabs(rot_error) < MIN_TURN) {
      double p_turn = TURN_KP * rot_error;
      double i_turn = TURN_KI * rot_sum;
      double d_turn = TURN_KD * (rot_error - rot_last);
      turn = p_turn + i_turn + d_turn;

      double p_power = STRAIGHT_KP * trans_error;
      double i_power = STRAIGHT_KI * trans_sum;
      double d_power = STRAIGHT_KD * (trans_error - trans_last);
      power = p_power + i_power + d_power;

    } else {
      double p_turn = TURN_KP * rot_error;
      double i_turn = TURN_KI * rot_sum;
      double d_turn = TURN_KD * (rot_error - rot_last);
      turn = p_turn + i_turn + d_turn;

      power = 0;
    }

    lcd::set_text(6, "trans: " + std::to_string(trans_error));
    lcd::set_text(7, "rot: " + std::to_string(rot_error));
    set_chassis(power + turn, power - turn);

    trans_last = trans_error;
    trans_sum += trans_error;
    rot_last = rot_error;
    rot_sum += rot_error;
  }
}

void chassis_task(void *parameter) {
  int time = 0;
  while (true) {
    odom_update(); //put only in auton later
    if (!competition::is_autonomous()) {
      tank_drive();
    } else {
      time += 10;
      //odom_update();
      chassis_auton();

      // display time elapsed, odom coords, and PID vars


    }
    lcd::set_text_color(255, 0, 0);
    lcd::set_text(0, "TIME: " + std::to_string(time));

    lcd::set_text_color(0, 0, 255);
    lcd::set_text(1, "X: " + std::to_string(int(100 * chassis_x) / 100.0));
    lcd::set_text(2, "Z: " + std::to_string(int(100 * chassis_z) / 100.0));
    lcd::set_text(3, "theta: " + std::to_string(int(180 * chassis_theta / M_PI)));

    delay(10);
  }
}
