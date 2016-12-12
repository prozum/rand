#ifndef RAND_TASK_H
#define RAND_TASK_H

#ifndef MOCK
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#include "fc/fc.h"
#include "core/io.h"
#include "sonar/sonar.h"
#include "ir/ir.h"
#include "laser/laser.h"
#include "nav/nav.h"
#include "map/map.h"

#define ONE_MS 63 // defines 1 millisecond
#define ONE_AND_A_HALF_MS 94 // defines 1.5 millisecond
#define TWO_MS 125 // defines 2 millisecond
#define MAJOR_CYCLE 6250 // 100 ms
#define MINOR_CYCLE 1125
#define SCHEDULER_OVERFLOW (MAJOR_CYCLE + ONE_MS) // 100 ms + 1 ms

#define TIMER_TICK_TO_MILIS(x) ((x) / ONE_MS)

#define YAW         P8
#define ROLL        P9
#define PITCH       P10
#define THROTTLE    P11

#define SONAR_TIMEOUT 11 * ONE_MS
#define SONAR_TRIGGER_PIN P2
#define SONAR_ECHO_PIN P3
#define IR_BOTTOM_PIN A0
#define IR_TOP_PIN A1

#define MAP_HEIGHT 64
#define MAP_WIDTH 64
#define CLEAN 1
#define DONT_CLEAN 0

sonar_t *sonar;
laser_t *laser;
ir_t *top_ir;
ir_t *bottom_ir;
fc_t *fc;
search_t *search_data;


void task_timer_setup();

/*pre-timer initialization*/
void init_not_timed();

/*flight controller tasks*/
void task_arm_fc();
void task_disarm_fc();
void task_init_fc();
void task_pulse();

/*sensor tasks*/
void task_read_laser();
void task_read_ir();
void task_read_sonar();
void task_read_acceleration();

/*machine intelligence task*/
void task_navigation();


#endif //RAND_TASK_H
