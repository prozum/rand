#ifndef RAND_TASK_H
#define RAND_TASK_H

/** @file task.h
 * \brief Task functions and data
 *
 * \addtogroup Task
 * @{
 */

#ifndef MOCK
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#include "fc/fc.h"
#include "core/io.h"
#include "sonar/sonar.h"
#include "ir/ir.h"
#include "laser/laser.h"
#include "map/map.h"
#include "nav/nav-struct.h"
#include "nav/nav.h"

#define ONE_MS 63            //!< Defines 1 millisecond
#define ONE_AND_A_HALF_MS 94 //!< Defines 1.5 millisecond
#define TWO_MS 125           //!< Defines 2 millisecond
#define MAJOR_CYCLE 6250     //!< 100 ms
#define MINOR_CYCLE 1125
#define SCHEDULER_OVERFLOW (MAJOR_CYCLE + ONE_MS) //!< 100 ms + 1 ms

#define YAW         P8
#define ROLL        P9
#define PITCH       P10
#define THROTTLE    P11

//! This allows the speed to travel 4.42 meters thus a bit above the cap of 2.2 meters
#define SONAR_TIMEOUT 13 * ONE_MS
#define SONAR_TRIGGER_PIN P2
#define SONAR_ECHO_PIN P3
#define IR_BOTTOM_PIN A0
#define IR_TOP_PIN A1

#define CLEAN 1
#define DONT_CLEAN 0

nav_t *nav_state;
rep_t *world_rep;
fc_t *fc;
laser_t *laser;
sonar_t *sonar;
search_t *search_data;
ir_t *bottom_ir;
ir_t *top_ir;


void task_timer_setup();

/* Pre-timer initialization */
void init_not_timed();

/* Flight controller tasks */
void task_arm_fc();
void task_disarm_fc();
void task_init_fc();
void task_pulse();

/* Sensor tasks*/
void task_read_laser_right();
void task_read_laser_front();
void task_read_laser_left();
void task_read_ir();
void task_read_sonar();
void task_read_acceleration();

/* Machine intelligence task */
void task_navigation();

#endif //RAND_TASK_H

//! @}
