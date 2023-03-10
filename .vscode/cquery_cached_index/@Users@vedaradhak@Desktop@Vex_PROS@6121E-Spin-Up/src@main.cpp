//Authors: Ved Radhakrishnan, Jan Iyer
//main file where the autonomous routines and the driver control functions are called.

#include "main.h"

void on_center_button() {
	static bool pressed = false;
	pressed = !pressed;
	if (pressed) {
		pros::lcd::set_text(2, "I was pressed!");
	} else {
		pros::lcd::clear_line(2);
	}
}

void initialize() {
	pros::lcd::initialize();

	chassis_unlock();
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
	red_left_roller();
	// right_roller();

}

void opcontrol() {

}
