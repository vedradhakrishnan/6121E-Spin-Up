#pragma once

#include "EZ-Template/drive/drive.hpp"

extern Drive chassis;
void set_chassis(double inches, int left, int right);
void drive_example();
void turn_example();
void prog_skills();
void wait_until_change_speed();
void swing_example();
void combining_movements();
void interfered_example();



void left_comp_auton();
void right_comp_auton();

void default_constants();
void one_mogo_constants();
void two_mogo_constants();