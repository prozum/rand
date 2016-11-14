#ifndef RAND_TASK_H
#define RAND_TASK_H

#include <util/delay.h>
#include <avr/interrupt.h>

#include "task.h"
#include "fc/fc.h"
#include "core/io.h"

void task_timer_setup();

void task_arm_fc();

void task_start_pulse();

void task_stop_pulse();

#endif //RAND_TASK_H
