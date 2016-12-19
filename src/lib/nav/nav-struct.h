#ifndef RAND_NAV_STRUCT_H_H
#define RAND_NAV_STRUCT_H_H

/** @file nav-struct.h
 * \brief Navigation structs
 *
 * \addtogroup Navigation
 * @{
 */

#include "fc/fc.h"
#include "ir/ir.h"
#include "laser/laser.h"
#include "search/search.h"
#include "sonar/sonar.h"

/**
 * The drone only performs one task at any time
 * this type defines that task.
 */
typedef enum task_e {
    IDLE,
    TURNING,
    MOVEFORWARD,
    MOVEUP,
    MOVEDOWN,
    FOLLOW_FORWARD,
    FOLLOW_FURTHER,
    FOLLOW_CHECK,
    FOLLOW_TURN,
    SEARCHING
} task_t;

/**
 * Defines the state of the drone's macihne intelligence
 */
typedef struct state_s {
    uint8_t wall_front : 1;    //!< Wall within 40cm in front
    uint8_t wall_right : 1;    //!< Wall within 40cm on the right
    uint8_t wall_left : 1;     //!< Wall within 40cm on the left
    uint8_t win_front : 1;     //!< Window within 40cm in front
    uint8_t win_right : 1;     //!< Window within 40cm on the right
    uint8_t win_left : 1;      //!< Window within 40cm on the left
    uint8_t win_check : 1;     //!< Window checked
    uint8_t ground : 1;        //!< Floor within 40cm below
    uint8_t ceiling : 1;       //!< Ceiling within 40cm above
    uint8_t blocked_front : 1; //!< There is either a window or WALL in front
    uint8_t blocked_left : 1;  //!< Either a window or WALL on the left
    uint8_t blocked_right : 1; //!< Either a window or WALL on the right
    uint8_t follow_left : 1;   //!< Follow left wall
    uint8_t follow_right : 1;  //!< Follow right wall
    uint8_t follow : 1;        //!< Follow right or left wall
} state_t;

/**
 * A data-structure for defining the drone's world representation
 */
typedef struct rep_s {
    fc_t *fc;        //!< A pointer to the data-structure for the drone's flight-controller
    laser_t *laser;  //!< A pointer to the data-structure for the drone's laser
    sonar_t *sonar;  //!< A pointer to the data-structure for the drone's sonar
    ir_t *ir_top;    //!< A pointer to the data-structure for the drone's IR pointing upwards
    ir_t *ir_bottom; //!< A pointer to the data-structure for the drone's IR pointing downwards
} rep_t;

/**
 * A data-structure for storing the drone's navigational state
 */
typedef struct nav_s {
    state_t state;          //!< Stores the state of the drone
    task_t task;            //!< Stores the task at hand
    fix16_t angle;          //!< Stores the drone's current heading in radians
    uint16_t posx;          //!< Stores the drone's x-position
    uint16_t posy;          //!< Stored the drone's y-position
    int16_t prev_dist_wall; //!< Stores the previously measured distance to the wall
    fix16_t val;            //!< A value for keeping track of how much a given task has been completed
    search_t search_data;   //!< Stores search-data, which is used when the drone should find a path to some point
} nav_t;

#endif // RAND_NAV_STRUCT_H_H

//! @}
