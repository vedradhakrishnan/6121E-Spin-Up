#include "main.h"
#include "pros/imu.hpp"

ADIEncoder odom_left(ENCODER_PORT_TL, ENCODER_PORT_BL, false);
ADIEncoder odom_center(ENCODER_PORT_TC, ENCODER_PORT_BC, false);
ADIEncoder odom_right(ENCODER_PORT_TR, ENCODER_PORT_BR, true);

ADIDigitalOut expansion(EXPANSION_PORT, LOW);
ADIDigitalOut indexer(INDEXER_PORT);

Motor drive_bl(DRIVE_MOTOR_PORT_BL, pros::E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);
Motor drive_br(DRIVE_MOTOR_PORT_BR, pros::E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_fl(DRIVE_MOTOR_PORT_FL, pros::E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_fr(DRIVE_MOTOR_PORT_FR, pros::E_MOTOR_GEARSET_18, false, E_MOTOR_ENCODER_COUNTS);

Motor intake(INTAKE_PORT, pros::E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor roller(ROLLER_PORT, pros::E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

// Motor indexer(INDEXER_PORT, pros::E_MOTOR_GEARSET_18, true, E_MOTOR_ENCODER_COUNTS);
Motor flywheel_front(FLYWHEEL_PORT_FRONT, pros::E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor flywheel_back(FLYWHEEL_PORT_BACK, pros::E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

//sensors
Imu imu1(IMU_PORT_1);
Imu imu2(IMU_PORT_2);

//need to defined the externed motors for the flywheel

Controller controller(E_CONTROLLER_MASTER);
