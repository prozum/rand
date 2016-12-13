#ifndef RAND_NAV_H
#define RAND_NAV_H

#define FULL_TURN 90
#define MAX_NEGATIVE_ACCELERATION 0
#define NO_ACCELERATION 1
#define MAX_POSITIVE_ACCELERATION 2
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 50
#define MIN_RANGE 60
#define LASER_MAX_DISTANCE_CM 2200

#define SONAR_DEG 15
#define PERPENDICULAR 90
#define DRONE_RIGHT_SIDE 27000
#define LASER_MAX_RANGE 2200
#define DRONE_LEFT_SIDE 9000

#define SENSOR_DEVIATION 5
#define MIN_DIFF_LASER_SONAR 30

#include <stdint.h>

#include "fc/fc.h"
#include "kalman/kalman_datafusion.h"
#include "kalman/kalman.h"
#include "core/log.h"
#include "map/map.h"
#include "libfixmath/fix16.h"

#define PERIOD_MILLIS 100 //The time between calls of the navigator.
#define PERIODS_PER_SEC 1000 / PERIOD_MILLIS

#define MAP_MIDDLE 800

//todo: skal udregnes ud fra WCET af løkken i findpath funktionen
#define ALLOWED_SEARCH_ITERATIONS 10

typedef struct rep_s{
    fc_t *fc;
    laser_t *laser;
    sonar_t *sonar;
    ir_t *ir_top;
    ir_t *ir_bottom;
}rep_t;

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

typedef enum side_e{
    right = 0,
    left = 1
}side_t;

typedef struct state_s{
    uint8_t AWallF      : 1; //WALL within 40cm in front
    uint8_t AWallR      : 1; //WALL within 40cm on the right
    uint8_t AWallL      : 1; //WALL within 40cm on the left
    uint8_t AWinF       : 1; //window within 40cm in front
    uint8_t AWinR       : 1; //window within 40cm on the right
    uint8_t AWinL       : 1; //window within 40cm on the left
    uint8_t AGround     : 1; //floor within 40cm below
    uint8_t ACeiling    : 1; //ceiling within 40cm above
    uint8_t BlockedF    : 1; //there is either a window or WALL in front
    uint8_t BlockedL    : 1; //either a window or WALL on the left
    uint8_t BlockedR    : 1; //either a window or WALL on the right
}state_t;

void update_state(state_t *state, rep_t *rep);

#define ANGLE_RESOLUTION 0.01                       // Means that each degree is split in 100
#define INV_ANGLE_RESOLUTION (1 / ANGLE_RESOLUTION) // One degree is 100 steps on the scale

typedef struct search_node_s search_node_t;

struct search_node_s{
    pixel_coord_t pos;
    search_node_t *parent;
    uint8_t gscore;
    uint8_t fscore;
    uint8_t valid;
};

typedef struct search_s{
    search_node_t *closed_set;
    search_node_t *open_set;
    uint16_t closedset_size;
    uint16_t openset_size;
    pixel_coord_t goal;
    uint8_t active;
}search_t;

typedef enum set_e{
    OPEN,
    CLOSED
}set_t;

#define INV_ANGLE_RESOLUTION 100 //One degree is 100 steps on the scale
typedef struct nav_s{
    state_t state;
    uint16_t timer;
    task_t task;
    uint16_t angle;
    uint16_t posx;
    uint16_t posy;
    int16_t previousDistanceToWall;
    fix16_t val;
    search_t search_data;
}nav_t;

void init_nav(nav_t *nav);

void navigation(rep_t *rep, nav_t *nav);

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep);

uint8_t CheckAWallF(rep_t *rep, state_t state);
uint8_t CheckAWallL(rep_t *rep);
uint8_t CheckAWallR(rep_t *rep);
uint8_t CheckAWinF(rep_t *rep, state_t state);
uint8_t CheckAWinL(rep_t *rep);
uint8_t CheckAWinR(rep_t *rep);
uint8_t CheckAGround(rep_t *rep);
uint8_t CheckACeiling(rep_t *rep);
uint8_t CheckBlockedF(state_t *state);
uint8_t CheckBlockedR(state_t *state);
uint8_t CheckBlockedL(state_t *state);

void onIdle(rep_t *rep, nav_t *nav);
void onMoveforward(rep_t *rep, nav_t *nav);
void onMoveup(rep_t *rep, nav_t *nav);
void onMovedown(rep_t *rep, nav_t *nav);
void onSearching(rep_t *rep, nav_t *nav);
void onTurning(rep_t *rep, nav_t *nav);
uint8_t isSonarReliable(rep_t *rep, state_t state);
uint8_t checkAlignmentToWall(rep_t *rep, nav_t *nav);
void drawMap (rep_t *rep, nav_t *nav);

void Idle(rep_t *rep, nav_t *nav);
void Turnleft(rep_t *rep, nav_t *nav, uint8_t degrees);
void Turnright(rep_t *rep, nav_t *nav, uint8_t degrees);
void Turnaround(rep_t *rep, nav_t *nav);
void Moveforward(rep_t *rep, nav_t *nav, fix16_t distance);
void Moveup(rep_t *rep, nav_t *nav);
void Movedown(rep_t *rep, nav_t *nav);
void Searching(rep_t *rep, nav_t *nav);

void map_set_point(uint8_t x, uint8_t y, fieldstate_t field);
void map_set_position(nav_t *nav, fieldstate_t field);
fieldstate_t map_check_point(uint8_t x, uint8_t y);
fieldstate_t map_check_position(nav_t *nav);

pixel_coord_t align_to_pixel(uint16_t x_coord, uint16_t y_coord);

fix16_t fix_rad_angle(uint16_t degrees_100th);
fix16_t calculate_y_distance(uint16_t degrees_100th, fix16_t distance);
fix16_t calculate_x_distance(uint16_t degrees_100th, fix16_t distance);
void update_angle(nav_t *nav, fix16_t degrees);

void init_search(search_t *search);
search_node_t* findpath(nav_t *nav);
search_node_t* addnode(search_t *list, search_node_t node, set_t set);
search_node_t* close_node(search_t *list, search_node_t *node);
void add_neighbours(search_t *list, search_node_t *node);
uint8_t estimate(search_node_t *node, pixel_coord_t pos);
search_node_t lowestf(search_t *search);


#endif //RAND_NAV_H


