#ifndef RAND_POSITIONING_H
#define RAND_POSITIONING_H

#define MAX_NEGATIVE_ACCELERATION 0
#define NO_ACCELERATION 1
#define MAX_POSITIVE_ACCELERATION 2
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 0.5
#define MIN_SAFE_DIST 0.4

#define DATAFUSION_FILTERS 1
#define SENSOR_FILTERS 4
#define MIN_RANGE 40

#include <stdint.h>

#include "fc/fc.h"
#include "kalman/kalman_datafusion.h"
#include "kalman/kalman.h"
#include "core/log.h"
#include "map/map.h"

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
    idle,
    turnleft,
    turnaround,
    turnright,
    moveforward,
    moveup,
    movedown,
    searching
}task_t;

typedef struct state_s{
    uint8_t AWallF      : 1; //wall within 40cm in front
    uint8_t AWallR      : 1; //wall within 40cm on the right
    uint8_t AWallL      : 1; //wall within 40cm on the left
    uint8_t AWinF       : 1; //window within 40cm in front
    uint8_t AWinR       : 1; //window within 40cm on the right
    uint8_t AWinL       : 1; //window within 40cm on the left
    uint8_t AGround     : 1; //floor within 40cm below
    uint8_t ACeiling    : 1; //ceiling within 40cm above
}state_t;

void update_state(state_t *state, rep_t *rep);

typedef struct nav_s{
    state_t *state;
    uint8_t *timer;
    task_t task;
    uint16_t *angle;
}nav_t;

kalman_state *kalman_filters[SENSOR_FILTERS];
kalman_state_matrix *datafusion_filters[DATAFUSION_UNITS];

position_t *positioning_init(float a[SENSOR_FILTERS], float r[SENSOR_FILTERS],
                             float A[DATAFUSION_FILTERS], float B[DATAFUSION_FILTERS]);

void positioning_calibrate(position_t *position, float sensor_initial_readings[SENSOR_FILTERS],
                           float df_initial_readings[2*DATAFUSION_FILTERS]);

void positioning_calculate(position_t *position, float sensor_readings[SENSOR_FILTERS],
                           float df_readings[2 * DATAFUSION_FILTERS]);

void update_u_k();

void navigation(rep_t *rep, nav_t *nav);

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep);

uint8_t CheckAWallF(rep_t *rep);
uint8_t CheckAWallL(rep_t *rep);
uint8_t CheckAWallR(rep_t *rep);
uint8_t CheckAWinF(rep_t *rep);
uint8_t CheckAWinL(rep_t *rep);
uint8_t CheckAWinR(rep_t *rep);
uint8_t CheckAGround(rep_t *rep);
uint8_t CheckACeiling(rep_t *rep);

void onIdle();
void onTurnleft();
void onTurnright();
void onTurnaround();
void onMoveforward();
void onMoveup();
void onMovedown();
void onSearching();


#endif //RAND_POSITIONING_H


