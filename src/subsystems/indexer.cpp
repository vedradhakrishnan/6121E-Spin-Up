#include "main.h"

int last_engagement = INDEXER_ENGAGE_COOLDOWN;
int burst_left = 0;

void indexer_task(void *parameter) {
  while (true) {

    if (!competition::is_autonomous()) {
      indexer_control();
    }

    last_engagement += 10;
    delay(10);
  }
}

void engage_indexer() {
  if (last_engagement > INDEXER_ENGAGE_COOLDOWN) {
    last_engagement = 0;
  }
}

void burst_indexer() {
  if (burst_left == 0 && last_engagement > INDEXER_ENGAGE_COOLDOWN) {
    burst_left = 3;
  }
}

void indexer_control() {
  if (controller.get_digital(DIGITAL_A)) {
    engage_indexer();
  } else if(controller.get_digital(DIGITAL_B)) {
    burst_indexer();
  }

  if (last_engagement < INDEXER_ENGAGE_COOLDOWN) {
    indexer.set_value(HIGH);
  } else {
    indexer.set_value(LOW);
  }

  if (burst_left > 0 && last_engagement > INDEXER_ENGAGE_COOLDOWN) {
    engage_indexer();
    burst_left--;
  }
}
