#include "main.h"

void indexer_task(void *parameter) {
  while (true) {
    // controller.set_text(1, 1, "LIFT: " + std::to_string((int)(bar_lift.get_position())));

    if (!competition::is_autonomous()) {
      indexer_control();
    }

    delay(10);
  }
}

void set_indexer(int voltage) {
  indexer = voltage;
}

void indexer_control() {
  if (controller.get_digital(DIGITAL_A)) {
    set_indexer(INDEXER_POWER);
  } else if(controller.get_digital(DIGITAL_B)) {
    set_indexer(INDEXER_REV_POWER);
  } else
    set_indexer(0);
}
