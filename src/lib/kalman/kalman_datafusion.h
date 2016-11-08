#include <stdint.h>
#include "core/io.h"
#include "core/log.h"

/*We're doing a specific implementation of the Kalman filter for two units (laser + sonar)*/
#define DATAFUSION_UNITS 2

typedef struct kalman_matrix_state_t {
    log_sender source_components;

    float a; //How much we assume the next measurement differs from the previous one
    float b; //Weight of control-input in next estimate
    float C[DATAFUSION_UNITS]; //Noise scale constant
    float R[DATAFUSION_UNITS][DATAFUSION_UNITS]; //variance of sensor, i.e. how much a measurement tends to differ from the actual

    float u_k; //Control signal
    float z_k[DATAFUSION_UNITS]; //Current observation
    float G_k[DATAFUSION_UNITS]; //kalman gain matrix
    float p_k; //prediction error matrix

    float x_k; //State variable

} kalman_state_matrix;

void kalman_datafusion_init (kalman_state_matrix *state, float a, float b, float p_0, log_sender component,
                             const float C[DATAFUSION_UNITS], const float R[DATAFUSION_UNITS][DATAFUSION_UNITS]);
void kalman_datafusion_setC (kalman_state_matrix *state, const float *values);
void kalman_datafusion_setR (kalman_state_matrix *state, const float values[DATAFUSION_UNITS][DATAFUSION_UNITS]);

void kalman_datafusion_filter (kalman_state_matrix *state, float z_laser, float z_sonar);

