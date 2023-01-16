#include "main.h"

//bot constants
#define CHASSIS_WIDTH 12.20
#define TRACKING_DIAM 2.75
#define TRACKING_WIDTH 5.75
// #define
// #define
#define INDEXER_ENGAGE_TIME 100



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
#define FLYWHEEL_POWER_HIGH 110
#define FLYWHEEL_POWER_LOW 100
#define INDEXER_POWER 95
#define INDEXER_REV_POWER -100

#define FLYWHEEL_PORT_FRONT 5
#define FLYWHEEL_PORT_BACK 6

//flywheel

//need to extern the motors for the front and the back flywheels

//defining the power and the ports for the intake
#define INTAKE_POWER 127
#define OUTTAKE_POWER -90
#define ROLLER_POWER 127
#define ROLLER_POS -1400

#define INTAKE_PORT 7
#define INDEXER_PORT 8

//intake
extern Motor intake;
extern Motor indexer;
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

extern ADIDigitalOut expansion_left;
#define EXPANSION_PISTON_L 'G'
#define EXPANSION_PISTON_R 'H'

extern ADIDigitalOut piston_indexer;
#define INDEXER_PORT_ADI 'G'


extern ADIEncoder odom_left;
extern ADIEncoder odom_center;
extern ADIEncoder odom_right;

//defining the V5 ports on the brain
#define DRIVE_MOTOR_PORT_BL 1
#define DRIVE_MOTOR_PORT_BR 2
#define DRIVE_MOTOR_PORT_FL 3
#define DRIVE_MOTOR_PORT_FR 4


//drive
extern Motor drive_bl;
extern Motor drive_br;
extern Motor drive_fl;
extern Motor drive_fr;


//Controller
extern Controller controller;
