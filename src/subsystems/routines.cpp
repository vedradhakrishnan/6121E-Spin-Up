#include "chassis.hpp"
#include "flywheel.hpp"
#include "indexer.hpp"
#include "intake.hpp"
#include "main.h"
#include "pros/rtos.h"
#include "pros/rtos.hpp"

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
  straight_pid(9, 30);
  intake.move_relative(-1200, ROLLER_POWER);
  delay(1500);

  straight_pid(-12, 80);

}

void red_right_disc() {
  straight_pid(12, 70);
  delay(1500);

  toggle_intake();
  straight_pid(12, 70);
  delay(1500);

  toggle_intake();
  straight_pid(12, 70);
  delay(1500);

  turn_pid(105, 80);
  delay(1000);

  set_flywheel(114);//MAGIC NUM
  delay(1000);

  turn_pid(100, 80);
  delay(2000);

  engage_indexer();
  delay(1500);
  engage_indexer();
  delay(1500);
  engage_indexer();
  delay(200);
  set_flywheel(LOW);//MAGIC NUM


}

void test_routine() {
  // turn_pid(45, 80);
  // delay(1500);
  // turn_pid(-45, 80);
  // delay(1500);
  // turn_pid(-90, 80);
  // delay(2000);
  // turn_pid(90, 80);
  // delay(2000);
  // turn_pid(180, 80);
  // delay(3500);
  // turn_pid(-360, 80);
  turn_pid(-1800, 70);
}
