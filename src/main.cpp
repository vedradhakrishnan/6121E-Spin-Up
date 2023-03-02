#include "main.h"
#include "autons.hpp"


// Chassis constructor
Drive chassis (
  // Left Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  {-7, 17, -19}

  // Right Chassis Ports (negative port will reverse it!)
  //   the first port is the sensored port (when trackers are not used!)
  ,{10, 18, -20}

  // IMU Port
  ,4 // 4

  // Wheel Diameter (Remember, 4" wheels are actually 4.125!)
  //    (or tracking wheel diameter)
  ,3.25
  // ,2.75

  // Cartridge RPM
  //   (or tick per rotation if using tracking wheels)
  ,600

  // External Gear Ratio (MUST BE DECIMAL)
  //    (or gear ratio of tracking wheel)
  // eg. if your drive is 84:36 where the 36t is powered, your RATIO would be 2.333.
  // eg. if your drive is 36:60 where the 60t is powered, your RATIO would be 0.6.
  ,5.0/3.0
  // ,1


  // Uncomment if using tracking wheels
  
  // // Left Tracking Wheel Ports (negative port will reverse it!)
  // // ,{1, 2} // 3 wire encoder
  // ,11 // Rotation sensor

  // // Right Tracking Wheel Ports (negative port will reverse it!)
  // // ,{-3, -4} // 3 wire encoder
  // ,-14 // Rotation sensor
  

  // Uncomment if tracking wheels are plugged into a 3 wire expander
  // 3 Wire Port Expander Smart Port
  // ,1
);



/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::print_ez_template();
  
  pros::delay(500); // Stop the user from doing anything while legacy ports configure.

  // Configure your chassis controls
  chassis.toggle_modify_curve_with_controller(true); // Enables modifying the controller curve with buttons on the joysticks
  chassis.set_active_brake(0); // Sets the active brake kP. We recommend 0.1.
  chassis.set_curve_default(0, 0); // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)  
  default_constants(); // Set the drive to your own constants from autons.cpp!

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.set_left_curve_buttons (pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT); // If using tank, only the left side is used. 
  // chassis.set_right_curve_buttons(pros::E_CONTROLLER_DIGITAL_Y,    pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  // ez::as::auton_selector.add_autons({
  //   Auton("Example Drive\n\nDrive forward and come back.", drive_example),
  //   Auton("Example Turn\n\nTurn 3 times.", turn_example),
  //   Auton("Drive and Turn\n\nDrive forward, turn, come back. ", drive_and_turn),
  //   Auton("Drive and Turn\n\nSlow down during drive.", wait_until_change_speed),
  //   Auton("Swing Example\n\nSwing, drive, swing.", swing_example),
  //   Auton("Combine all 3 movements", combining_movements),
  //   Auton("Interference\n\nAfter driving forward, robot performs differently if interfered or not.", interfered_example),
  // });

  // Initialize chassis and auton selector
  chassis.initialize();
  // ez::as::initialize();

  // Add tasks here
  // Task chassis(chassis_task);
	Task flywheel(flywheel_task);
	Task indexer(indexer_task);
	Task intake(intake_task);
	Task expansion(expansion_task);
	Task tilter(tilter_task);
  // Task chassis(chassis_task);
  // opcontrol();
  
}



/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // opcontrol();
}



/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}



/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.reset_pid_targets(); // Resets PID targets to 0
  chassis.reset_gyro(); // Reset gyro position to 0
  chassis.reset_drive_sensor(); // Reset drive sensors to 0
  chassis.set_drive_brake(MOTOR_BRAKE_HOLD); // Set motors to hold.  This helps autonomous consistency.

  // ez::as::auton_selector.call_selected_auton(); // Calls selected auton from autonomous selector.
  // drive_example();
  // turn_example();
  //prog_skills();
  left_comp_auton();
}



/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
  // This is preference to what you like to drive on.
  chassis.set_drive_brake(MOTOR_BRAKE_COAST);

  while (true) {

    // chassis.tank(); // Tank control

    int left_stick = controller.get_analog(E_CONTROLLER_ANALOG_LEFT_Y);
    int right_stick = controller.get_analog(E_CONTROLLER_ANALOG_RIGHT_Y);

    if(abs(left_stick) < 10) left_stick = 0;
    if(abs(right_stick) < 10) right_stick = 0;

    // lcd::set_text(4, "left: " + std::to_string(left_stick));
    // lcd::set_text(5, "right: " + std::to_string(right_stick));

    // set_chassis(left_stick, right_stick);
    chassis.left_motors[0] = left_stick;
    chassis.left_motors[1] = left_stick;
    chassis.left_motors[2] = left_stick;

    chassis.right_motors[0] = right_stick;
    chassis.right_motors[1] = right_stick;
    chassis.right_motors[2] = right_stick;

    // tank_left = -right_stick;
    // tank_right = -left_stick;

    // chassis.arcade_standardN(ez::SPLIT); // Standard split arcade
    // chassis.arcade_standard(ez::SINGLE); // Standard single arcade
    // chassis.arcade_flipped(ez::SPLIT); // Flipped split arcade
    // chassis.arcade_flipped(ez::SINGLE); // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .

    pros::delay(ez::util::DELAY_TIME); // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}
