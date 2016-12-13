#ifndef RAND_NAV_STRUCT_H_H
#define RAND_NAV_STRUCT_H_H

#include "fc/fc.h"
#include "laser/laser.h"
#include "sonar/sonar.h"
#include "ir/ir.h"
#include "search/search.h"

/**
 * The drone only performs one task at any time
 * this type defines that task.
 */
typedef enum task_e{
    IDLE,
    TURNING,
    MOVEFORWARD,
    MOVEUP,
    MOVEDOWN,
    SEARCHING
}task_t;

typedef struct state_s{
    uint8_t wall_front      : 1; // Wall within 40cm in front
    uint8_t wall_right      : 1; // Wall within 40cm on the right
    uint8_t wall_left       : 1; // Wall within 40cm on the left
    uint8_t win_front       : 1; // Window within 40cm in front
    uint8_t win_right       : 1; // Window within 40cm on the right
    uint8_t win_left        : 1; // Window within 40cm on the left
    uint8_t ground          : 1; // Floor within 40cm below
    uint8_t ceiling         : 1; // Ceiling within 40cm above
    uint8_t blocked_front   : 1; // There is either a window or WALL in front
    uint8_t blocked_left    : 1; // Either a window or WALL on the left
    uint8_t blocked_right   : 1; // Either a window or WALL on the right
}state_t;

typedef struct rep_s{
    fc_t *fc;
    laser_t *laser;
    sonar_t *sonar;
    ir_t *ir_top;
    ir_t *ir_bottom;
}rep_t;

typedef struct nav_s{
    state_t state;
    task_t task;
    uint16_t timer;
    uint16_t angle;
    uint16_t posx;
    uint16_t posy;
    int16_t prev_dist_wall;
    fix16_t val;
    search_t search_data;
}nav_t;

#endif //RAND_NAV_STRUCT_H_H
