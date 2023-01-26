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
  straight_pid(18, 100);
  delay(3000);
  // turn_const(90, 70);
  straight_pid(-12, 100);
}
