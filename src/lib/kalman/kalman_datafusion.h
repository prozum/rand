#include <stdint.h>
#include "core/io.h"
#include "core/log.h"

/*We're doing a specific implementation of the Kalman filter for two units (laser + sonar)*/
#define DATAFUSION_UNITS 2
#define ZLASER 0
#define ZSONAR 1

typedef struct kalman_matrix_state_t {
    log_sender source_components;

    float a; //How much we assume the next measurement differs from the previous one
    float b; //Weight of control-input in next estimate
    float **C; //Noise scale constant[]
    float **R; //variance of sensor, i.e. how much a measurement tends to differ from the actual [][]

    float u_k; //Control signal
    float **z_k; //Current observation []
    float **G_k; //kalman gain vector   []
    float p_k; //prediction error matrix

    float x_k; //State variable

} kalman_state_matrix;

void kalman_datafusion_init(kalman_state_matrix *state, float a, float b, float p_0, log_sender component,
                            const float **C, const float **R);

void kalman_datafusion_filter(kalman_state_matrix *state, float z_laser, float z_sonar);

void kalman_datafusion_calibrate(kalman_state_matrix *state, float z_0_laser, float z_0_sonar);

