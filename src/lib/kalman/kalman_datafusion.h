#ifndef RAND_KALMAN_DF_H
#define RAND_KALMAN_DF_H

#include <stdint.h>
#include "core/log.h"
#include "matrix/matrix.h"
#include <math.h>

/*We're doing a specific implementation of the Kalman filter for two units (laser + sonar)*/
#define DATAFUSION_UNITS 2
#define ZLASER 0
#define ZSONAR 1

typedef struct kalman_matrix_state_s {
    log_sender source_components;

    fix16_t a; //How much we assume the next measurement differs from the previous one
    fix16_t b; //Weight of control-input in next estimate
    matrix_t *C; //Noise scale constant[]
    matrix_t *R; //variance of sensor, i.e. how much a measurement tends to differ from the actual [][]

    fix16_t u_k; //Control signal
    matrix_t *z_k; //Current observation []
    matrix_t *G_k; //kalman gain vector   []
    fix16_t p_k; //prediction error matrix

    fix16_t x_k; //State variable

} kalman_state_matrix;

kalman_state_matrix *kalman_datafusion_init (fix16_t a, fix16_t b, log_sender component,
                             matrix_t *C, matrix_t *R);
void kalman_datafusion_filter (kalman_state_matrix *state, fix16_t z_laser, fix16_t z_sonar);
void kalman_datafusion_calibrate (kalman_state_matrix *state, fix16_t z_0_laser, fix16_t z_0_sonar);

#endif //RAND_KALMAN_DF_H

