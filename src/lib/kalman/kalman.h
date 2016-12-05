#ifndef RAND_SINGLE_KALMAN_H
#define RAND_SINGLE_KALMAN_H

#include <stdint.h>
#include <stdlib.h>
#include "core/log.h"

typedef struct kalman_state_t {
    log_sender source_components;

    float a; //How much we assume the next measurement differs from the previous one
    float r; //variance of sensor, i.e. how much a measurement tends to differ from the actual

    float z_k; //Current observation
    float g_k; //kalman gain variable
    float p_k; //prediction error variable

    float x_k; //State variable
    float u_k; // control signal

} kalman_state;

kalman_state *kalman_init(float _a, float _r, log_sender component);

void kalman_run(kalman_state *state, float z_k);

void kalman_calibrate(kalman_state *initial_state, float z_0);

#endif //RAND_SINGLE_KALMAN_H

