#pragma once
#include "main.h"

void flywheel_task(void *);

void set_flywheel(int voltage);

void flywheel_control();

void set_flywheel_velocity(int v);
void set_flywheel_tbh();
