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

void left_roller() {
  rollers();
  delay(1600);

  straight_pid(-18, 127);


}

void left_roller_and_disc() {
  straight_pid(6, 30);
  intake.move_relative(-300, ROLLER_POWER);
  delay(800);

  straight_pid(-2.5, 80);
  delay(1200);

  turn_pid(-21.5, 120);
  set_flywheel(121.6);//MAGIC NUM
  delay(1000);

  // turn_pid(35, 80);
  delay(2000);

  engage_indexer();
  delay(2500);
  engage_indexer();
  delay(200);
  set_flywheel(LOW);//MAGIC NUM
  turn_pid(-110, 110);
  delay(1400);
  straight_pid(30, 127);

  delay(1200);

  toggle_intake();
  straight_pid(20, 60);
  delay(2000);
  turn_pid(83, 120);
  set_flywheel(116);
  delay(2100);
  engage_indexer();
  
  

}



void right_roller_and_disc() {
  set_flywheel(112);
  straight_pid(-30, 110);
  delay(1500);
  turn_pid(18, 80);
  delay(1000);
  // set_flywheel(115);
  // delay(3000);
  engage_indexer();
  delay(700);
  engage_indexer();
}








void test_routine() {
  straight_pid(12, 70);
  delay(1500);

  toggle_intake();
  straight_pid(12, 70);
  delay(1500);

  toggle_intake();
  straight_pid(12, 70);
}
