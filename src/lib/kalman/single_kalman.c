#include "single_kalman.h"

void single_kalman_init (kalman_state *state, double _a, double _r, log_sender component)
{
    state->a = _a;
    state->r = _r;

    state->p_k = 10;

    //State and control-signal
    state->x_k = 0;

    state->source_components = component;
}

double single_kalman_run (kalman_state *state, double z_k)
{
    // the x_k and p_k we use in the calculations are those of the previous calculation
    // so we calculate a new x_k and p_k based on the previous values

    // x̂_k = a * x̂_k−1
    state->x_k = state->a * state->x_k;

    // p_k = a * p_k−1 * a
    state->p_k = state->a * state->p_k * state->a;

    // g_k = p_k / (p_k + r)
    state->g_k = state->p_k / (state->p_k + state->r);

    // x̂_k = x̂_k + g_k * (z_k − x̂_k)
    state->x_k = state->x_k + state->g_k * (state->z_k - state->x_k);

    // p_k = (1 − g_k) * p_k
    state->p_k = (1 - state->g_k) * state->p_k;

    return state->x_k;
}