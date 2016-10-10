#include "kalman.h"
#include <stdlib.h>

void kalman_init (kalman_state *state, uint8_t size, log_sender component)
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

    state->source_components = component;

    check_for_null_matrix(state);
}

void check_for_null_matrix(kalman_state *state) {
    if(!state->A || !state->B || !state->C || !state->R || !state->G_k || !state->P_k)
        LOG_ERROR(state->source_components, "Kalman-state failed to allocate space for a matrix.");
}

void kalman_setA (kalman_state *state, const double *values)
{
   
}

void kalman_setB (kalman_state *state, const double *values)
{

}

void kalman_setC (kalman_state *state, const double *values)
{

}

void kalman_setR (kalman_state *state, const double *values)
{

}

void kalman_filter (kalman_state* state, double measurement)
{

}

void kalman_update(kalman_state* state, double measurement)
{

}

void kalman_filter(kalman_state *state, double measurement) {

}