#ifndef RAND_KALMAN_DF_H
#define RAND_KALMAN_DF_H

/** @file kalman-datafusion.h
 * \brief Kalman datafusion functions and data
 *
 * \addtogroup KalmanDatafusion
 * @{
 */

#include <stdint.h>
#include "core/log.h"
#include "matrix/matrix.h"
#include <math.h>

//! This is a specific implementation of the Kalman filter for two units (laser + sonar)
#define DATAFUSION_UNITS 2 //!< Defines the maximum number of sensors thay may be used in the filter
#define ZLASER 0 //!< Defines the vector-index for the laser's readings
#define ZSONAR 1 //!< Defines the vector-index for the sonar's readings

/**
 * A data-structure for storing the state of the data-fusion filter
 */
typedef struct kalman_matrix_state_s {
    log_sender_t source_components; //!< The component the filter is applied to

    fix16_t a;   //!< How much we assume the next measurement differs from the previous one
    fix16_t b;   //!< Weight of control-input in next estimate
    matrix_t *C; //!< Noise scale constant[]
    matrix_t *R; //!< Variance of sensor, i.e. how much a measurement tends to differ from the actual [][]

    fix16_t u_k;   //!< Control signal
    matrix_t *z_k; //!< Current observation []
    matrix_t *G_k; //!< Kalman gain vector   []
    fix16_t p_k;   //!< Prediction error matrix

    fix16_t x_k; //!< State variable

} kalman_state_matrix;

/**
 * Initializes a Kalman filter for use in datafusion with 2 sensors
 * @param a - The expected change of the system in percent / 100
 * @param b - The weight of the control-input when estimating
 * @param component - The component the filter is connected to (used for logging)
 * @param C - 1 x N matrix with constants
 * @param R - N x N diagonal matrix with sensor variances
 * @return - A pointer to the newly allocated datafusion-filter
 */
kalman_state_matrix *kalman_datafusion_init (fix16_t a, fix16_t b, log_sender_t component,
                             matrix_t *C, matrix_t *R);
/**
 * Filter a new set of readings
 * @param state - A pointer to the filter-struct
 * @param z_laser - The latest reading from the sensor
 * @param z_sonar - The latest reading from the sonar
 */
void kalman_datafusion_filter (kalman_state_matrix *state, fix16_t z_laser, fix16_t z_sonar);
/**
 * Calibrate the filter to the initial readings
 * @param state - The filter to calibrate
 * @param z_0_laser - The initial laser reading
 * @param z_0_sonar - The initial sonar reading
 */
void kalman_datafusion_calibrate (kalman_state_matrix *state, fix16_t z_0_laser, fix16_t z_0_sonar);

#endif //RAND_KALMAN_DF_H

//! @}
