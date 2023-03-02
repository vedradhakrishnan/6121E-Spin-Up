#pragma once

#include "main.h"
#include "pros/imu.hpp"

//bot constants
#define CHASSIS_WIDTH 12.20
#define TRACKING_DIAM 2.75
#define TRACKING_WIDTH 5.75
// #define
// #define
#define AUTON_TIME 15000
#define CONTROL_TIME 105000
#define EXPANSION_TIME 10000


//chassis constants
#define STRAIGHT_KP 8.625 //original value 13.25
#define STRAIGHT_KI 0.0
#define STRAIGHT_KD -7.5

#define SLANT_KP 60.0
#define SLANT_KI 0.0
#define SLANT_KD -12.5

#define TURN_KP 200.0
#define TURN_KI 0.0
#define TURN_KD -2.0

#define BRAKE_TIME 40

#define DRIVE_BRAKE 1
#define DRIVE_PID 2
#define DRIVE_TANK 3
// #define DRIVE_CONST 3

#define MAX_ACCEL_SLEW 10
#define MAX_DECEL_SLEW 256

#define MAX_STRAIGHT 110
#define MAX_TURN 80

#define MIN_TURN 0.25
#define MIN_ROT_ERROR 0.02
#define MIN_TRANS_ERROR 0.05

//Flywheel constants
#define FLYWHEEL_POWER_HIGH 100
#define FLYWHEEL_POWER_LOW 90
#define FLYWHEEL_VEL_HIGH 550
#define FLYWHEEL_VEL_LOW 450

#define FLYWHEEL_GAIN 0.5
#define INDEXER_POWER 95
#define INDEXER_REV_POWER -100

#define FLYWHEEL_PORT 9
// #define FLYWHEEL_PORT_BACK 11

#define IMU_PORT_1 4
#define IMU_PORT_2 5
//flywheel

//need to extern the motors for the front and the back flywheels

//defining the power and the ports for the intake
#define INTAKE_POWER 114
#define OUTTAKE_POWER -127
#define ROLLER_POWER 127
#define ROLLER_POS -1400

#define INTAKE_PORT 1
// #define ROLLER_PORT 20

extern ADIDigitalOut indexer;
#define INDEXER_PORT 'A'
#define INDEXER_ENGAGE_COOLDOWN 180
#define INDEXER_ENGAGE_TIME 50


//intake
extern Motor intake;
// extern Motor roller;

// extern Motor indexer;
extern Motor flywheel;
// extern Motor flywheel_back;


//odom and chassis motor definition
//defining the ADI ports for use with the encoders
// #define ENCODER_PORT_TL 'A'
// #define ENCODER_PORT_BL 'B'
// #define ENCODER_PORT_TC 'C'
// #define ENCODER_PORT_BC 'D'
// #define ENCODER_PORT_TR 'E'
// #define ENCODER_PORT_BR 'F'

extern ADIDigitalOut tilter;
#define TILTER_PORT 'B'

extern ADIDigitalOut expansion;
#define EXPANSION_PORT 'C'


// extern ADIEncoder odom_left;
// extern ADIEncoder odom_center;
// extern ADIEncoder odom_right;

//defining the V5 ports on the brain
#define DRIVE_MOTOR_PORT_FR 7
#define DRIVE_MOTOR_PORT_R 17
#define DRIVE_MOTOR_PORT_TR 19

#define DRIVE_MOTOR_PORT_FL 10
#define DRIVE_MOTOR_PORT_BL 18
#define DRIVE_MOTOR_PORT_TL 20



//drive
extern Motor drive_bl;
extern Motor drive_br;
extern Motor drive_fl;
extern Motor drive_fr;

//Sensors
extern Imu imu1;
extern Imu imu2;


//Controller
extern Controller controller;
