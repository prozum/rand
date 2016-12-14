#ifndef RAND_SINGLE_KALMAN_H
#define RAND_SINGLE_KALMAN_H

#include <stdint.h>
#include <stdlib.h>
#include "core/log.h"
#include "libfixmath/fix16.h"

typedef struct kalman_state_t {
    log_sender source_components;

    fix16_t a; //How much we assume the next measurement differs from the previous one
    fix16_t r; //variance of sensor, i.e. how much a measurement tends to differ from the actual

    fix16_t z_k; //Current observation
    fix16_t g_k; //kalman gain variable
    fix16_t p_k; //prediction error variable

    fix16_t x_k; //State variable
    fix16_t u_k; // control signal

} kalman_state;

/**
 * Initialize a Kalman filter for use on a single sensor
 * @param _a - The estimated change of the system in percentage / 100
 * @param _r - The variance of the sensor
 * @param component - The component the filter is attached to (used only for logging)
 * @return - A pointer to the newly allocated kalman_state
 */
kalman_state *kalman_init(fix16_t _a, fix16_t _r, log_sender component);

/**
 * Run the Kalman filter on a new input-value
 * @param state - A pointer to the kalman state
 * @param z_k - The latest value read by the filtered sensor
 */
void kalman_run(kalman_state *state, fix16_t z_k);

/**
 * Calibrate the filter to align first estimation with first reading
 * @param initial_state - A pointer to the Kalman state to calibrate
 * @param z_0 - The first reading taken by the given sensor
 */
void kalman_calibrate(kalman_state *initial_state, fix16_t z_0);

#endif //RAND_SINGLE_KALMAN_H

