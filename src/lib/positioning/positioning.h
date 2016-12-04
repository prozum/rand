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

#include <stdint.h>

#include "fc/fc.h"
#include "kalman/kalman_datafusion.h"
#include "kalman/kalman.h"
#include "core/log.h"

#define FRONT_a 0.99
#define SIDE_a 1
#define TOP_BOT_a 1
#define SONAR_r 1
#define LASER_r 1
#define IR_r 1
#define KALMAN_b 0 //We do not take the control signal into account as of now.

#define FRONT_READING 0
#define LEFT_READING 0
#define RIGHT_READING 1
#define TOP_READING 2
#define BOTTOM_READING 3

typedef struct position_s {
    /*Fill here*/
} position_t;

kalman_state *kalman_filters[SENSOR_FILTERS];
kalman_state_matrix *datafusion_filters[DATAFUSION_UNITS];

position_t *positioning_init(float a[SENSOR_FILTERS], float r[SENSOR_FILTERS],
                             float A[DATAFUSION_FILTERS], float B[DATAFUSION_FILTERS]);

void positioning_calibrate(position_t *position, float sensor_initial_readings[SENSOR_FILTERS],
                           float df_initial_readings[2*DATAFUSION_FILTERS]);

void positioning_calculate(position_t *position, float sensor_readings[SENSOR_FILTERS],
                           float df_readings[2 * DATAFUSION_FILTERS]);

void update_u_k();

void navigation(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *ir_top, ir_t *ir_bottom);

#endif //RAND_POSITIONING_H


