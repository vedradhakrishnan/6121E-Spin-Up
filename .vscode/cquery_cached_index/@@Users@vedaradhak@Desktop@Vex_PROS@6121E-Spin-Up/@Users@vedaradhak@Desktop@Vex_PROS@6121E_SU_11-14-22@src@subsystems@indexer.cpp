#include "main.h"

int last_engagement = INDEXER_ENGAGE_TIME;

void indexer_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      indexer_control();
    }

    last_engagement += 10;
    delay(10);
  }
}

void set_indexer(int voltage) {
  indexer = voltage;
}

void engage_piston_indexer() {
  if (last_engagement > INDEXER_ENGAGE_TIME) {
    last_engagement = 0;
  }
}

void indexer_control() {
  // if (controller.get_digital(DIGITAL_A)) {
  //   set_indexer(INDEXER_POWER);
  // } else if(controller.get_digital(DIGITAL_B)) {
  //   set_indexer(INDEXER_REV_POWER);
  // } else
  //   set_indexer(0);
  if (controller.get_digital(DIGITAL_A)) {
    engage_piston_indexer();
  }

  if (last_engagement < INDEXER_ENGAGE_TIME) {
    piston_indexer.set_value(HIGH);
  } else
    piston_indexer.set_value(LOW);
}
