#include "main.h"

ADIEncoder odom_left(ENCODER_PORT_TL, ENCODER_PORT_BL, false);
ADIEncoder odom_center(ENCODER_PORT_TC, ENCODER_PORT_BC, false);
ADIEncoder odom_right(ENCODER_PORT_TR, ENCODER_PORT_BR, true);

Motor drive_bl(DRIVE_MOTOR_PORT_BL, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);
Motor drive_br(DRIVE_MOTOR_PORT_BR, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_fl(DRIVE_MOTOR_PORT_FL, E_MOTOR_GEARSET_06, true, E_MOTOR_ENCODER_COUNTS);
Motor drive_fr(DRIVE_MOTOR_PORT_FR, E_MOTOR_GEARSET_06, false, E_MOTOR_ENCODER_COUNTS);

Controller controller(E_CONTROLLER_MASTER);
