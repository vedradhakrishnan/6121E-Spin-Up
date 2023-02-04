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
  set_flywheel(120);//MAGIC NUM
  delay(100);
  set_intake(-127);
  delay(110);

  set_intake(0);
  straight_pid(-5, 80);
  delay(1200);

  turn_pid(-20, 80);
  delay(1500);

  // turn_pid(35, 80);
  // delay(2000);

  engage_indexer();
  delay(2000);
  engage_indexer();
  delay(200);
  set_flywheel(LOW);//MAGIC NUM
  turn_pid(-102, 80);
  delay(1400);
  straight_pid(30, 127);

  delay(1000);

  set_intake(INTAKE_POWER);
  straight_pid(20, 35);
  delay(2600);
  set_flywheel(120);
  turn_pid(75, 80);
  set_flywheel(116);
  delay(2100);
  set_intake(0);
  engage_indexer();
  
  

}



void right_roller_and_disc() {
  
  // toggle_intake();
  set_intake(INTAKE_POWER);
  straight_pid(30, 65);
  delay(2700);
  set_flywheel(115);
  
  

  turn_pid(-154, 80);
  
  // straight_pid(-2, 60);
  

  // toggle_intake();
  set_intake(0);

  delay(3400);
  engage_indexer();
  delay(1500);
  engage_indexer();
  delay(1500);
  // straight_pid(2, 60);
  engage_indexer();
  delay(200);
  set_flywheel(LOW);
  delay(200);

  turn_pid(-57, 80);
  delay(770);
  straight_pid(41, 100);
  delay(2800);
  turn_pid(41, 80);
  delay(600);
  straight_pid(7, 120);
  delay(400);
  // intake.move_relative(-300, ROLLER_POWER);
  set_intake(-127);
  delay(130);
  set_intake(0);
  straight_pid(-2, 70);
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
