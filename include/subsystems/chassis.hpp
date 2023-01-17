#pragma once
#include "main.h"

//HELPERS
double tracker_inches(int ticks);
void chassis_lock();
void chassis_unlock() ;
void initialize_aps(double x_i, double z_i, double theta_i);

void set_chassis(int left, int right);
void odom_update_aps();
void straight_const(double inches, int power);
void turn_const(double degrees, int power);
void straight_pid(double inches, int power);


void tank_drive();

void drive_brake();

void chassis_auton();

void chassis_task(void *);
