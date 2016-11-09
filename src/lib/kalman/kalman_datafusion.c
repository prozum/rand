#include "kalman_datafusion.h"
#include "matrix/matrix.h"
#include <stdlib.h>
#include <math.h>

void setC(kalman_state_matrix *state, const float **values);
void setR(kalman_state_matrix *state, const float **values);

void kalman_datafusion_init (kalman_state_matrix *state, float a, float b, float p_0, log_sender component,
                             const float** C, const float** R)
{
    state->source_components = component;
    state->a = a;
    state->b = b;
    state->p_k = p_0;
    state->u_k = 1;
    state->G_k[0][0] = 0;
    state->G_k[1][0] = 1;

    setC(state, C);
    setR(state, R);
}

void setC (kalman_state_matrix *state, const float **values)
{
    int i = 0;

    for (i; i < DATAFUSION_UNITS; ++i) {
        state->C[i][0] = values[i][0];
    }
}

void setR (kalman_state_matrix *state, const float **values)
{
    int i = 0, j = 0;

    for (i; i < DATAFUSION_UNITS; ++i) {
        for (j; j < DATAFUSION_UNITS; j++) {
            state->R[i][j] = values[i][j];
        }
    }
}

void kalman_datafusion_predict (kalman_state_matrix* state)
{
    //x_k = a * x_k + b * u_k (predict the next state from the previous and the control signal)
    state->x_k = state->a * state->x_k + state->b * state->u_k;
    //p_k = a^2 * x_k (calculate the uncertainty)
    state->p_k = pow(state->a, 2) * state->x_k;
}

void kalman_datafusion_update(kalman_state_matrix* state)
{
    float **cT = trans_matrix(state->C, 1, 2);

    float **inv = inv_mat(add_mat_mat(mult_mat_mat(mult_const_vec(state->C, state->p_k, 1), cT, 2, 1, 1, 2), state->R, 2));

    //G_k = inv * (p * cT)
    state->G_k = mult_mat_mat(mult_const_vec(cT, state->p_k, 3), inv, 1, 2, 2, 2);

    //x = x+ G * (z - (C*x))
    state->x_k = state->x_k + mult_mat_mat(state->G_k, sub_vec_vec(state->z_k, mult_const_vec(state->C, state->x_k, 1), 2), 2, 2, 2, 2)[0][0];

    state->p_k = (1 - mult_mat_mat(state->G_k, state->C, 1, 2, 2, 2)[0][0]) * state->p_k;


}

void kalman_datafusion_filter(kalman_state_matrix *state, float z_laser, float z_sonar) {
    //Create a vector of the current readings.
    state->z_k[0][0] = z_laser;
    state->z_k[1][0] = z_sonar;
    //Filter
    kalman_datafusion_predict(state);
    kalman_datafusion_update(state);
}