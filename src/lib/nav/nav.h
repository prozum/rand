#ifndef RAND_NAV_H
#define RAND_NAV_H

#define FULL_TURN 90
#define MAX_NEGATIVE_ACCELERATION 0
#define NO_ACCELERATION 1
#define MAX_POSITIVE_ACCELERATION 2
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 0.5
#define MIN_SAFE_DIST 0.4

#define DATAFUSION_FILTERS 1
#define SENSOR_FILTERS 4
#define MIN_RANGE 60

#define SONAR_DEG 15
#define PERPENDICULAR 90
#define DRONE_RIGHT_SIDE 270
#define DRONE_LEFT_SIDE 90

#define SONAR_DEVIATION 5
#define MIN_DIFF_LASER_SONAR 30
#define GRID_SIZE 25 //width/height of a map field in cm

#include <stdint.h>

#include "fc/fc.h"
#include "kalman/kalman_datafusion.h"
#include "kalman/kalman.h"
#include "core/log.h"
#include "map/map.h"
#include "libfixmath/fix16.h"

#define FRONT_a 0.99
#define SIDE_a 1
#define TOP_BOT_a 1
#define SONAR_r 1
#define LASER_r 1
#define IR_r 1
#define KALMAN_b 0 //We do not take the control signal into account as of now.
#define PERIOD 100 //The time between calls of the navigator.

#define FRONT_READING 0
#define LEFT_READING 0
#define RIGHT_READING 1
#define TOP_READING 2
#define BOTTOM_READING 3

typedef struct position_s {
    /*Fill here*/
} position_t;

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
    TURNLEFT,
    TURNAROUND,
    TURNRIGHT,
    MOVEFORWARD,
    MOVEUP,
    MOVEDOWN,
    SEARCHING
}task_t;

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

typedef struct nav_s{
    state_t state;
    uint16_t timer;
    task_t task;
    uint16_t angle;
    int8_t posx;
    int8_t posy;
    uint16_t val;
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
void onTurnleft(rep_t *rep, nav_t *nav);
void onTurnright(rep_t *rep, nav_t *nav);
void onTurnaround(rep_t *rep, nav_t *nav);
void onMoveforward(rep_t *rep, nav_t *nav);
void onMoveup(rep_t *rep, nav_t *nav);
void onMovedown(rep_t *rep, nav_t *nav);
void onSearching(rep_t *rep, nav_t *nav);
uint8_t isSonarReliable(rep_t *rep, state_t state);

void Idle(rep_t *rep, nav_t *nav);
void Turnleft(rep_t *rep, nav_t *nav, uint8_t degrees);
void Turnright(rep_t *rep, nav_t *nav, uint8_t degrees);
void Turnaround(rep_t *rep, nav_t *nav);
void Moveforward(rep_t *rep, nav_t *nav);
void Moveup(rep_t *rep, nav_t *nav);
void Movedown(rep_t *rep, nav_t *nav);
void Searching(rep_t *rep, nav_t *nav);

void Map_set_point(nav_t *nav, uint8_t x, uint8_t y, fieldstate_t field);
fieldstate_t Map_Check_point(nav_t nav, uint8_t x, uint8_t y);


#endif //RAND_NAV_H


