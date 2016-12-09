#include <libfixmath/fix16.h>
#include "kalman/kalman.h"

kalman_state *kalman_init(fix16_t _a, fix16_t _r, log_sender component) {
    kalman_state *state = malloc(sizeof(kalman_state));

    //Insufficient memory on the heap, call for a safe-landing
    if(!state) {
        ERROR("Not enough heap-space for Kalman filter.");
    }

    state->a = _a;
    state->r = _r;

    //Uncertainty values
    state->p_k = fix16_from_int(10);
    state->g_k = fix16_from_int(0);

    //State and control-signal
    state->x_k = fix16_from_int(0);
    state->u_k = fix16_from_int(0);

    state->source_components = component;
}

void kalman_run(kalman_state *state, fix16_t z_k) {
    if (!state)
        return;

    state->z_k = z_k;

    // the x_k and p_k we use in the calculations are those of the previous calculation
    // so we calculate a new x_k and p_k based on the previous values

    // x̂_k = a * x̂_k−1
    state->x_k = fix16_mul(state->a, state->x_k);

    // p_k = a * p_k−1 * a
    state->p_k = fix16_mul(fix16_mul(state->a, state->a), state->p_k);

    // g_k = p_k / (p_k + r)
    state->g_k = fix16_div(state->p_k, fix16_add(state->p_k, state->r));

    // x̂_k = x̂_k + g_k * (z_k − x̂_k)
    state->x_k = fix16_add(state->x_k, fix16_mul(state->g_k, fix16_sub(state->z_k, state->x_k)));

    // p_k = (1 − g_k) * p_k
    state->p_k = fix16_mul(fix16_sub(fix16_from_int(1), state->g_k), state->p_k);
}

void kalman_calibrate(kalman_state *initial_state, fix16_t z_0) {
    uint8_t calibration_done = 0;
    while (!calibration_done) {
        kalman_run(initial_state, z_0);

        fix16_t diff = fix16_sub(initial_state->x_k, z_0);

        if (diff <= initial_state->r)
            calibration_done = 1;
    }
}