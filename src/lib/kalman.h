#include <stdint.h>
#include "io.h"

typedef struct {
    const uint8_t size;
    log_sender source_components;

    double *A; //Weight of previous measurement in next estimate
    const double *B; //Weight of control-input in next estimate
    const double *C; //Noise scale constant
    const double *R; //variance of sensor, i.e. how much a measurement tends to differ from the actual

    double u_k; //Control signal
    double z_k; //Current observation
    double *G_k; //kalman gain matrix
    double *P_k; //prediction error matrix

} kalman_state;

void kalman_init (kalman_state *state, const uint8_t size, log_sender component);
void kalman_setA (kalman_state *state, const double *values);
void kalman_setB (kalman_state *state, const double *values);
void kalman_setC (kalman_state *state, const double *values);
void kalman_setR (kalman_state *state, const double *values);
void kalman_filter (kalman_state* state, double measurement);

