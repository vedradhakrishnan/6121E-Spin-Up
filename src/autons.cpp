#include "autons.hpp"
#include "main.h"
#include "pros/rtos.hpp"
#include "subsystems/flywheel.hpp"
#include "subsystems/indexer.hpp"
#include "subsystems/intake.hpp"
#include "subsystems/tilter.hpp"


/////
// For instalattion, upgrading, documentations and tutorials, check out website!
// https://ez-robotics.github.io/EZ-Template/
/////


const int DRIVE_SPEED = 110; // This is 110/127 (around 87% of max speed).  We don't suggest making this 127.
                             // If this is 127 and the robot tries to heading correct, it's only correcting by
                             // making one side slower.  When this is 87%, it's correcting by making one side
                             // faster and one side slower, giving better heading correction.
const int TURN_SPEED  = 90;
const int SWING_SPEED = 90;



///
// Constants
///

// It's best practice to tune constants when the robot is empty and with heavier game objects, or with lifts up vs down.
// If the objects are light or the cog doesn't change much, then there isn't a concern here.

void default_constants() {
  chassis.set_slew_min_power(60, 60);
  chassis.set_slew_distance(3, 3);
  chassis.set_pid_constants(&chassis.headingPID, 12.5, 0, 21.3, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.00220, 0.00001, 0.024, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.0023, 0, 0.038, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 3.6, 0, 0, 0);
}

void one_mogo_constants() {
  chassis.set_slew_min_power(70, 70);
  chassis.set_slew_distance(7, 7);
  chassis.set_pid_constants(&chassis.headingPID, 16, 0, 36, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.40, 0, 9.6, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.40, 0, 9.6, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}

void two_mogo_constants() {
  chassis.set_slew_min_power(80, 80);
  chassis.set_slew_distance(1, 1);
  chassis.set_pid_constants(&chassis.headingPID, 11, 0, 20, 0);
  chassis.set_pid_constants(&chassis.forward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.backward_drivePID, 0.45, 0, 5, 0);
  chassis.set_pid_constants(&chassis.turnPID, 5, 0.003, 35, 15);
  chassis.set_pid_constants(&chassis.swingPID, 7, 0, 45, 0);
}


void modified_exit_condition() {
  // chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  // chassis.set_exit_condition(chassis.drive_exit, 80, 50, 300, 150, 500, 500);

  // chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 100, 500);
  // chassis.set_exit_condition(chassis.swing_exit, 0, 0, 0, 0, 0, 0);
  // chassis.set_exit_condition(chassis.drive_exit, 100, 50, 300, 150, 100, 500);

  chassis.set_exit_condition(chassis.turn_exit, 100, 3, 500, 7, 80, 500);
  chassis.set_exit_condition(chassis.swing_exit, 100, 3, 500, 7, 500, 500);
  chassis.set_exit_condition(chassis.drive_exit, 80, 50, 150, 150, 80, 500);
}




///
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater then the slew distance + a few inches
  // one_mogo_constants();
  modified_exit_condition();

  chassis.set_drive_pid(3, 20);
  delay(20);
  set_intake(-ROLLER_POWER);
  delay(200);  
  set_intake(0);

  chassis.set_drive_pid(-10.5, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  set_intake(110);
  chassis.set_drive_pid(31, 30, true);
  //chassis.wait_drive();
  delay(3050);  

  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(3, 20);
  // set_intake(-ROLLER_POWER);
  delay(250);  

  chassis.set_drive_pid(-3, DRIVE_SPEED, true);
  chassis.wait_drive();
  set_flywheel(110);
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-55, 50, true);
  // chassis.wait_until(53);
  chassis.wait_drive();
  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();


  for (int i = 0; i < 3; i++) {
    delay(500);
    engage_indexer();
  }
}



///
// Turn Example
///
void turn_example() {
  modified_exit_condition();

  // tilter.set_value(HIGH);
  // toggle_tilter();
  set_flywheel(104);
  // set_flywheel_velocity(500);
  
  delay(3000);
  engage_indexer();

  // set_flywheel_velocity(500);
  set_flywheel(107);
  delay(100);
  for (int i = 0; i < 8; i++) {
    delay(700);
    engage_indexer();
  }
  set_flywheel_velocity(LOW);
  delay(700);


  chassis.set_turn_pid(90, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(18.5, 90, true);
  chassis.wait_until(17);
  set_intake(120);
  chassis.wait_drive();

  delay(1000);
  chassis.set_drive_pid(12.5, 20, true);
  chassis.wait_drive();

  chassis.set_drive_pid(-10.5, 90, true);
  chassis.wait_drive();
}

void left_comp_auton() {
  modified_exit_condition();
  one_mogo_constants();


  //spin up
  set_flywheel(112);

  //get the roller
  set_intake(-ROLLER_POWER);
  chassis.set_drive_pid(2, 10, true);
  delay(200);


  //drive away
  chassis.set_drive_pid(-6, 20, true);

  set_intake(0);

  chassis.wait_drive();

  //aim

  chassis.set_turn_pid(-18, TURN_SPEED);

  delay(3000);

  //fire

  for (int i = 0; i < 2; i++) {
    delay(700);
    engage_indexer();
  }

  delay(500);

  //aim toward discs
  chassis.set_turn_pid(-135, TURN_SPEED);
  chassis.wait_drive();


  //lower flywheel speed
  set_flywheel(108);

  //knock over stack

  chassis.set_drive_pid(50, 120, true);

  chassis.wait_drive();

  delay(500);
  

  //intake the stack
  set_intake(118);

  chassis.set_drive_pid(60, 20, true);
  chassis.wait_drive();

  //aim
  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();


  //fire
  for (int i = 0; i < 3; i++) {
    delay(700);
    engage_indexer();
  }
  
}


///
// Combining Turn + Drive
///
void prog_skills() {
  modified_exit_condition();
  one_mogo_constants();


  chassis.set_angle(-10.25);
//   // sets the flywheel
//  // tilter.set_value(HIGH);
//   // toggle_tilter();
//   set_flywheel(104);
//   // set_flywheel_velocity(500);
  
//   //shoots the first set of match loads

//   delay(3000);
//   engage_indexer();


  // set_flywheel(107);
  // delay(100);
  // for (int i = 0; i < 8; i++) {
  //   delay(700);
  //   engage_indexer();
  // }
  set_flywheel(92);
  delay(700);

  //angles and drivesd forward

  chassis.set_drive_pid(-11.25, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turns and drives backwards
  chassis.set_turn_pid(20, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(44, 70, true);
  chassis.wait_drive();
  chassis.set_turn_pid(20, TURN_SPEED);
  chassis.wait_drive();

  //orients toward disc and intakes
  set_intake(114);
  chassis.set_turn_pid(7, TURN_SPEED);
  chassis.wait_drive();
  
  chassis.set_drive_pid(10, 15, true);
  
  chassis.wait_drive();


  delay(700);
  
  
  //chassis.set_turn_pid(5, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(16, 50, true);
  chassis.wait_drive();
  chassis.set_drive_pid(6, 20, true);
 
  set_intake(-ROLLER_POWER);
  chassis.wait_drive();
  
  
  delay(440);  
  set_intake(0);

  //drives back from roller
  chassis.set_drive_pid(-12.5, DRIVE_SPEED, true);
  chassis.wait_drive();

  //turns toward other roller
  chassis.set_turn_pid(-86, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(12.5, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-86, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_drive_pid(4, 10, true);

  //rolls roller
  set_intake(-ROLLER_POWER);
  

  delay(800);  
  set_intake(0);

  //drives away from roller
  chassis.set_drive_pid(-10, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-90, TURN_SPEED);


  //goes forward and shoots a disc
  chassis.set_drive_pid(-42, 80, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-86, TURN_SPEED);
  chassis.set_angle(-90);
  engage_indexer();

  
  chassis.wait_drive();
  chassis.set_drive_pid(16, DRIVE_SPEED, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-216, TURN_SPEED);
  chassis.wait_drive();
  chassis.set_angle(-225);

  //disc intake
  set_intake(118);

  chassis.set_drive_pid(70, 50, true);
  chassis.wait_drive();
  chassis.set_turn_pid(-135, TURN_SPEED);

  chassis.wait_drive();

  delay(100);
  for (int i = 0; i < 3; i++) {
    delay(700);
    engage_indexer();
  }

  
}



///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // wait_until will wait until the robot gets to a desired position


  // When the robot gets to 6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(-45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  // When the robot gets to -6 inches, the robot will travel the remaining distance at a max speed of 40
  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_until(-6);
  chassis.set_max_speed(40); // After driving 6 inches at DRIVE_SPEED, the robot will go the remaining distance at 40 speed
  chassis.wait_drive();
}



///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is target degrees
  // The third parameter is speed of the moving side of the drive


  chassis.set_swing_pid(ez::LEFT_SWING, 45, SWING_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_until(12);

  chassis.set_swing_pid(ez::RIGHT_SWING, 0, SWING_SPEED);
  chassis.wait_drive();
}



///
// Auto that tests everything
///
void combining_movements() {
  chassis.set_drive_pid(24, DRIVE_SPEED, true);
  chassis.wait_drive();

  chassis.set_turn_pid(45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_swing_pid(ez::RIGHT_SWING, -45, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_turn_pid(0, TURN_SPEED);
  chassis.wait_drive();

  chassis.set_drive_pid(-24, DRIVE_SPEED, true);
  chassis.wait_drive();
}



///
// Interference example
///
void tug (int attempts) {
  for (int i=0; i<attempts-1; i++) {
    // Attempt to drive backwards
    printf("i - %i", i);
    chassis.set_drive_pid(-12, 127);
    chassis.wait_drive();

    // If failsafed...
    if (chassis.interfered) {
      chassis.reset_drive_sensor();
      chassis.set_drive_pid(-2, 20);
      pros::delay(1000);
    }
    // If robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, robot will drive forward and turn 90 degrees. 
// If interfered, robot will drive forward and then attempt to drive backwards. 
void interfered_example() {
 chassis.set_drive_pid(24, DRIVE_SPEED, true);
 chassis.wait_drive();
//  chassis.set_swing_pid(e_swing type, double target, int speed)

 if (chassis.interfered) {
   tug(3);
   return;
 }

 chassis.set_turn_pid(90, TURN_SPEED);
 chassis.wait_drive();
}



// . . .
// Make your own autonomous functions here!
// . . .