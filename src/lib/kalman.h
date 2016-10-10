#include <stdint.h>
#include "io.h"

typedef struct {
    const uint8_t size;

    const double *A;
    const double *B;
    const double *C;
    const double *R;

    double u_k; //Control signal
    double z_k; //Current observation
    double *G_k; //kalman gain matrix
    double *P_k; //prediction error matrix

} kalman_state;

void kalman_init (kalman_state *state, const uint8_t size);
void kalman_setA (kalman_state *state, const double *values);
void kalman_setB (kalman_state *state, const double *values);
void kalman_setC (kalman_state *state, const double *values);
void kalman_setR (kalman_state *state, const double *values);
void kalman_filter (kalman_state* state, double measurement);

