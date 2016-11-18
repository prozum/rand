#ifndef RAND_TASK_H
#define RAND_TASK_H

#include <util/delay.h>
#include <avr/interrupt.h>

#include "fc/fc.h"
#include "core/io.h"

#define ONE_MS 63 // defines 1 millisecond
#define ONE_AND_A_HALF_MS 94 // defines 1.5 millisecond
#define TWO_MS 125 // defines 2 millisecond
#define MAJOR_CYCLE 6250 // 100 ms
#define MINOR_CYCLE 1125
#define OVERFLOW (MAJOR_CYCLE + ONE_MS) // 100 ms + 1 ms

#define YAW         P8
#define ROLL        P9
#define PITCH       P10
#define THROTTLE    P11

#define SONAR_TRIGGER_PIN 1
#define SONAR_ECHO_PIN 2

void task_timer_setup();

void task_arm_fc();
void task_disarm_fc();
void task_init_fc();
void task_pulse();

#endif //RAND_TASK_H
