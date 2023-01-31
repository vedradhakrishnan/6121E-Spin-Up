//Authors: Ved Radhakrishnan, Jan Iyer
//main file where the autonomous routines and the driver control functions are called.

#include "main.h"
#include "pros/motors.h"
#include "subsystems/globals.hpp"
#include "subsystems/routines.hpp"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}


//starts when program is run
void initialize() {
	pros::lcd::initialize();

	chassis_unlock();
	flywheel_back.set_brake_mode(E_MOTOR_BRAKE_COAST);
	flywheel_front.set_brake_mode(E_MOTOR_BRAKE_COAST);
	// expansion.set_value(LOW);

	controller.set_text(1, 0, "Project: Discus");

	pros::lcd::register_btn1_cb(on_center_button);

	//Add tasks here
	Task chassis(chassis_task);
	Task flywheel(flywheel_task);
	Task indexer(indexer_task);
	Task intake(intake_task);
	Task expansion(expansion_task);

	delay(500);

}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	// red_left_roller();
	// right_roller();
	test_routine();
}

void opcontrol() {

}
