#include "chassis.hpp"
#include "main.h"

void rollers() {
  straight_pid(9, 127);
  intake.move_relative(-1200, ROLLER_POWER);
  delay(1600);
  straight_pid(0, 127);
}

void red_left_roller() {
  rollers();
  delay(1600);

  straight_pid(-18, 127);


}

void blue_left_roller() {
  straight_pid(9, 127);

  delay(150);

}

void test_routine() {
  straight_pid(8, 100);
  delay(1500);
  // turn_const(90, 70);
  turn_pid(-45, 80);

  delay(2000);

  straight_pid(-8, 100);
  delay(1500);
  // turn_const(90, 70);
  straight_pid(-10, 80);

  delay(2500);
  turn_pid(90, 100);

  delay(2000);
  straight_pid(12, 100);

  // straight_pid(36, 70);

}
