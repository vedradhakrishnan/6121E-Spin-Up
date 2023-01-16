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
	controller.set_text(1, 0, "Ready to Go!");

	pros::lcd::register_btn1_cb(on_center_button);

	//Add tasks here
	Task chassis(chassis_task);

	delay(500);
	straight_pid(18, 100);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {

}

void opcontrol() {

}
