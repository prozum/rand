#ifndef RAND_TASK_H
#define RAND_TASK_H

/** @file task.h
 * \brief Task functions and data
 *
 * \addtogroup Task
 * @{
 */

#ifndef MOCK
#include <avr/interrupt.h>
#include <util/delay.h>
#endif

#include "core/io.h"
#include "fc/fc.h"
#include "ir/ir.h"
#include "laser/laser.h"
#include "map/map.h"
#include "nav/nav-struct.h"
#include "nav/nav.h"
#include "sonar/sonar.h"

#define ONE_MS 63                                 //!< Defines 1 millisecond
#define ONE_AND_A_HALF_MS 94                      //!< Defines 1.5 millisecond
#define TWO_MS 125                                //!< Defines 2 millisecond
#define MAJOR_CYCLE 6250                          //!< 100 ms, the length of the major cycle in ticks
#define MINOR_CYCLE 1125                          //!< 20 ms, the length of the major cycle in ticks
#define SCHEDULER_OVERFLOW (MAJOR_CYCLE + ONE_MS) //!< 100 ms + 1 ms

#define YAW P8       //!< The pin connected to the yaw-axis of the flight-controller
#define ROLL P9      //!< The pin connected to the roll-axis of the flight-controller
#define PITCH P10    //!< The pin connected to the pitch-axis of the flight-controller
#define THROTTLE P11 //!< The pin connected to the throttle-axis of the flight-controller

//! This allows the sound to travel 4.42 meters thus a bit above the cap of 2.2 meters
#define SONAR_TIMEOUT 13 * ONE_MS //!< The timeout for the sonar in ticks
#define SONAR_TRIGGER_PIN P2      //!< The trigger-pin for the sonar
#define SONAR_ECHO_PIN P3         //!< The echo-pin for the sonar
#define IR_BOTTOM_PIN A0          //!< The pin which the bottom ir is connected to
#define IR_TOP_PIN A1             //!< The pin which the top ir is connected to

#define CLEAN 1      //!< Defines the flag for cleaning the map
#define DONT_CLEAN 0 //!< Defines the flag for not cleaning the map

nav_t *nav_state;      //!< The current navigation state
rep_t *world_rep;      //!< The drone's world representation
fc_t *fc;              //!< A pointer to the struct representing the physical flight-controller
laser_t *laser;        //!< A pointer to the struct representing the laser
sonar_t *sonar;        //!< A pointer to the struct representing the sonar
search_t *search_data; //!< A pointer to a search struct used in the navigation component
ir_t *bottom_ir;       //!< A pointer to the struct representing the physical ir on the bottom of the drone
ir_t *top_ir;          //!< A pointer to the struct representing the physical ir on the top of the drone

/**
 * Function for setting up the timers for the scheduler
 */
void task_timer_setup();

/**
 * Function for setting up all variables that are not time-dependant
 */
void init_not_timed();

/**
 * Arms the flight-controller so that the drone is ready to take of
 */
void task_arm_fc();
/**
 * Disarms the flight-controller causing the drone to either safe-land or stay still no matter the input
 */
void task_disarm_fc();
/**
 * Initialize the flight-controller
 */
void task_init_fc();
/**
 * Pulse the flight-controller on all PWM inputs
 */
void task_pulse();

/**
 * Read the laser's value to the right
 */
void task_read_laser_right();
/**
 * Read the laser's value in front
 */
void task_read_laser_front();
/**
 * Read the laser's value to the left
 */
void task_read_laser_left();
/**
 * Read boths ir-sensors
 */
void task_read_ir();
/**
 * Ping and read the sonar
 */
void task_read_sonar();
/**
 * Read the acceleration from the flight-controller
 */
void task_read_acceleration();

/**
 * Navigates the drones and determines what actions to take
 */
void task_navigation();

#endif // RAND_TASK_H

//! @}
