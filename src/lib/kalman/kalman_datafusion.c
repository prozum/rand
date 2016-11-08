#include "kalman_datafusion.h"
#include "matrix/matrix.h"
#include <stdlib.h>

void check_for_null_matrix(kalman_state_matrix *state) {
    if(!state->A || !state->B || !state->C || !state->R || !state->G_k || !state->P_k)
        LOG_ERROR(state->source_components, "Kalman-state failed to allocate space for a matrix.");

    //It's quite bad, if the matrices are not malloc'ed - do we need some sort of abort flight function?
}

void kalman_datafusion_init (kalman_state_matrix *state, uint8_t size, log_sender component)
{
    //The matrix needs to have size rows and size columns, thus size * size must be malloc'ed
    uint8_t tot_size = size * size;

    //Malloc space for constants
    state->A = malloc(tot_size);
    state->B = malloc(tot_size);
    state->C = malloc(tot_size);
    state->R = malloc(tot_size);

    //And for variables
    state->G_k = malloc(tot_size);
    state->P_k = malloc(tot_size);

    //State and control-signal
    state->u_k = malloc(size);
    state->x_k = malloc(size);

    state->source_components = component;
    state->size = size;

    check_for_null_matrix(state);
}

void kalman_datafusion_destroy(kalman_state_matrix *state) {
    free(state->A);
    free(state->B);
    free(state->C);
    free(state->R);

    free(state->G_k);
    free(state->P_k);
    free(state->x_k);

    LOG(state->source_components, "This function nullifies the struct - do not use it again!");

    free(state);
}

void kalman_datafusion_setA (kalman_state_matrix *state, const double *values)
{
    uint8_t tot_size = state->size * state->size;

    if(state->A) {
        int i = 0;

        for (i; i < tot_size; ++i) {
            state->A[i] = values[i];
        }
    }
}

void kalman_datafusion_setB (kalman_state_matrix *state, const double *values)
{
    uint8_t tot_size = state->size * state->size;

    if(state->B) {
        int i = 0;

        for (i; i < tot_size; ++i) {
            state->B[i] = values[i];
        }
    }
}

void kalman_datafusion_setC (kalman_state_matrix *state, const double *values)
{
    uint8_t tot_size = state->size * state->size;

    if(state->C) {
        int i = 0;

        for (i; i < tot_size; ++i) {
            state->C[i] = values[i];
        }
    }
}

void kalman_datafusion_setR (kalman_state_matrix *state, const double *values)
{
    uint8_t tot_size = state->size * state->size;

    if(state->R) {
        int i = 0;

        for (i; i < tot_size; ++i) {
            state->R[i] = values[i];
        }
    }
}

void kalman_datafusion_predict (kalman_state_matrix* state, double measurement)
{
    //state->z_k = add_vec_vec(mult_mat_vec(state->C, state->x_k), state->v_k);

    //x_k = A*x_k + B*u_k
    /*state->x_k = add_vec_vec(mult_mat_vec(state->A, state->x_k), mult_mat_vec(state->B, state->u_k)); */
    //P_k = A * P_(k-1) * A^T
    /*state->P_k = add_mat_mat(mult_mat_mat(mult_mat_mat(state->A, state->P_k, state->size),
                                          mat_T(state->A), state->size));*/
}

void kalman_datafusion_update(kalman_state_matrix* state, double measurement)
{
    //C^T
    /*double *C_trans = mat_T(state->C);*/

    //G_k = P_k * C^T * (C * P_k * C^T + R)^-1
    /*state->G_k = mult_mat_mat(
            mult_mat_mat(state->P_k, C_trans, state->size),
                mat_inv(add_mat_mat(
                        mult_mat_mat(state->C, mult_mat_mat(state->P_k, C_trans, state->size),
                        state->R), state->size)),
            state->size);*/

    //x_k = x_k + G_k (z_k - C * x_k)
    /*state->x_k = add_vec_vec(state->x_k, mult_mat_vec(state->G_k,
                                                      sub_vec_vec(state->z_k, mult_mat_vec(state->C, state->x_k))));*/

    //P_k = (I - G_k * C) * P_k
    /*state->P_k = mult_mat_mat(sub_mat_mat(I, mult_mat_mat(state->G_k, state->C)), state->P_k);*/


}

void kalman_datafusion_filter(kalman_state_matrix *state, double measurement) {

}