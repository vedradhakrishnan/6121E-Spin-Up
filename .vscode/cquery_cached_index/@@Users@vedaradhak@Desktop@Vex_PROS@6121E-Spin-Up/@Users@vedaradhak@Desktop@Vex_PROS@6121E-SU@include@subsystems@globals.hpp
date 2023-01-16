#include "main.h"

//bot constants
#define CHASSIS_WIDTH 12.20
#define TRACKING_DIAM 2.75
#define TRACKING_WIDTH 5.75
// #define
// #define


//chassis constants
#define STRAIGHT_KP 2.0
#define STRAIGHT_KI 0.0
#define STRAIGHT_KD 0.0

#define TURN_KP 5.0
#define TURN_KI 0.0
#define TURN_KD 0.0

#define BRAKE_TIME 40

#define DRIVE_BRAKE 1
#define DRIVE_PID 2
#define DRIVE_CONST 3

#define MAX_STRAIGHT 110
#define MAX_TURN 80

#define MIN_TURN 0.25

//Flywheel constants
#define FLYWHEEL_POWER_AUTON 120
#define FLYWHEEL POWER_OPCONTROL 105
#define FLYWHEEL_PORT_FRONT 6
#define FLYWHEEL_PORT_BACK 7

#define INTAKE_POWER 100
#define INTAKE_PORT 5

//odom and chassis motor definition
#define ENCODER_PORT_TL 'A'
#define ENCODER_PORT_BL 'B'
#define ENCODER_PORT_TC 'C'
#define ENCODER_PORT_BC 'D'
#define ENCODER_PORT_TR 'E'
#define ENCODER_PORT_BR 'F'

extern ADIEncoder odom_left;
extern ADIEncoder odom_center;
extern ADIEncoder odom_right;


#define DRIVE_MOTOR_PORT_BL 1
#define DRIVE_MOTOR_PORT_BR 2
#define DRIVE_MOTOR_PORT_FL 3
#define DRIVE_MOTOR_PORT_FR 4

extern Motor drive_bl;
extern Motor drive_br;
extern Motor drive_fl;
extern Motor drive_fr;
//Controller
extern Controller controller;
