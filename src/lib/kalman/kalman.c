#include "kalman.h"
#include <stdlib.h>

void kalman_init (kalman_state *state, uint8_t size)
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

    if()
}

void kalman_update(kalman_state* state, double measurement)
{

}