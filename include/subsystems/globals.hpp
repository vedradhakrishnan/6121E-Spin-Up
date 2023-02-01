#pragma once
#include "main.h"

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
#define STRAIGHT_KP 13.25
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
#define FLYWHEEL_POWER_HIGH 110
#define FLYWHEEL_POWER_LOW 95
#define FLYWHEEL_GAIN 0.5
#define INDEXER_POWER 95
#define INDEXER_REV_POWER -100

#define FLYWHEEL_PORT_FRONT 12
#define FLYWHEEL_PORT_BACK 11

//flywheel

//need to extern the motors for the front and the back flywheels

//defining the power and the ports for the intake
#define INTAKE_POWER 97
#define OUTTAKE_POWER -97
#define ROLLER_POWER 127
#define ROLLER_POS -1400

#define INTAKE_PORT 10
#define ROLLER_PORT 20

extern ADIDigitalOut indexer;
#define INDEXER_PORT 'G'
#define INDEXER_ENGAGE_COOLDOWN 400
#define INDEXER_ENGAGE_TIME 100


//intake
extern Motor intake;
extern Motor roller;

// extern Motor indexer;
extern Motor flywheel_front;
extern Motor flywheel_back;


//odom and chassis motor definition
//defining the ADI ports for use with the encoders
#define ENCODER_PORT_TL 'A'
#define ENCODER_PORT_BL 'B'
#define ENCODER_PORT_TC 'C'
#define ENCODER_PORT_BC 'D'
#define ENCODER_PORT_TR 'E'
#define ENCODER_PORT_BR 'F'

extern ADIDigitalOut expansion;
#define EXPANSION_PORT 'H'


extern ADIEncoder odom_left;
extern ADIEncoder odom_center;
extern ADIEncoder odom_right;

//defining the V5 ports on the brain
#define DRIVE_MOTOR_PORT_BL 5
#define DRIVE_MOTOR_PORT_BR 6
#define DRIVE_MOTOR_PORT_FL 3
#define DRIVE_MOTOR_PORT_FR 4


//drive
extern Motor drive_bl;
extern Motor drive_br;
extern Motor drive_fl;
extern Motor drive_fr;


//Controller
extern Controller controller;
