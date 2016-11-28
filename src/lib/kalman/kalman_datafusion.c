#include "kalman_datafusion.h"

void setC(kalman_state_matrix *state, float **values);
void setR(kalman_state_matrix *state, float **values);
void calibrate_open_space(kalman_state_matrix*, float, float);

kalman_state_matrix *kalman_datafusion_init (float a, float b, log_sender component,
                             float** C, float** R)
{
    kalman_state_matrix *state = malloc(sizeof(kalman_state_matrix));
    //Not enough heap-space, abort flight.
    if(!state)
        ERROR("Failed to malloc space for the datafusion-matrix");

    state->source_components = component;
    state->a = a;
    state->b = b;
    state->p_k = 10;
    state->u_k = 1;
    state->G_k = matrix_constructor(1, 2);
    state->G_k->values[0][0] = 1;
    state->G_k->values[0][1] = 1;

    setC(state, C);
    setR(state, R);

    return state;
}

void setC (kalman_state_matrix *state, float **values)
{
    int i = 0;

    state->C = matrix_constructor(DATAFUSION_UNITS, 1);

    for (i; i < DATAFUSION_UNITS; ++i) {
        state->C->values[i][0] = values[i][0];
    }
}

void setR (kalman_state_matrix *state, float **values)
{
    int i = 0, j = 0;

    state->R = matrix_constructor(DATAFUSION_UNITS, DATAFUSION_UNITS);

    for (i; i < DATAFUSION_UNITS; ++i) {
        for (j; j < DATAFUSION_UNITS; j++) {
            state->R->values[i][j] = values[i][j];
        }
    }
}

void kalman_datafusion_predict(kalman_state_matrix *state) {
    //x_k = a * x_k + b * u_k (predict the next state from the previous and the control signal)
    state->x_k = state->a * state->x_k + state->b * state->u_k;
    //p_k = a^2 * x_k (calculate the uncertainty)
    state->p_k = pow(state->a, 2) * state->x_k;
}

void calculate_G(kalman_state_matrix *state) {
    //G = MatrixMatrixMultiply(p * Transpose(c), inv((MatrixMatrixMultiply(C * p, Transpose(C))+R)))

    //Calculate p * Transpose(c)
    matrix_t *CT = trans_matrix(state->C);
    matrix_t *CpT = mult_const_vec(CT, state->p_k);

    //calculate inv((MatrixMatrixMultiply(C * p, Transpose(C))+R))
    matrix_t *Cp = mult_const_vec(state->C, state->p_k);
    matrix_t *mm_CpCT = mult_mat_mat(Cp, CT);
    matrix_t *no_inv = add_mat_mat(mm_CpCT, state->R);
    matrix_t *inv = inv_mat(no_inv);

    //Free previous G and update with new one
    matrix_destructor(state->G_k);
    state->G_k = mult_mat_mat(CpT, inv);

    //clean up
    matrix_destructor(CT);
    matrix_destructor(CpT);
    matrix_destructor(Cp);
    matrix_destructor(mm_CpCT);
    matrix_destructor(no_inv);
    matrix_destructor(inv);
}

void calculate_x(kalman_state_matrix *state) {
    //x = x + MatrixMatrixMultiply(G, z - C * x)

    //calculate C * x + z
    matrix_t *Cx = mult_const_vec(state->C, state->x_k);
    matrix_t *zCx = add_vec_vec(state->z_k, Cx);

    //calculate MatrixMatrixMultiply(G, z - C * x)
    matrix_t *mmm = mult_mat_mat(state->G_k, zCx);

    //G_k is 1x2 and z - C * x is 2x1 so mmm is 1x1
    float res = state->x_k +  mmm->values[0][0];

    //Update x of the state
    state->x_k = res;

    //clean up
    matrix_destructor(Cx);
    matrix_destructor(zCx);
    matrix_destructor(mmm);
}

void calculate_p(kalman_state_matrix *state) {
    //p = (1 - MatrixMatrixMultiply(G, C)) * p

    matrix_t *mGC = mult_mat_mat(state->G_k, state->C); //G is 1x2 and C is 2x1 so result is 1x1
    float res = (1 - mGC->values[0][0]) * state->p_k;

    //update
    state->p_k = res;

    //clean up
    matrix_destructor(mGC);
}

void kalman_datafusion_update(kalman_state_matrix *state) {
    calculate_G(state);
    calculate_x(state);
    calculate_p(state);
}

void kalman_datafusion_filter(kalman_state_matrix *state, float z_laser, float z_sonar) {
    //Update the z-vector with the current readings.
    state->z_k->values[ZLASER][0] = z_laser;
    state->z_k->values[ZSONAR][0] = z_sonar;

    //Filter
    kalman_datafusion_predict(state);
    kalman_datafusion_update(state);
}

void kalman_datafusion_calibrate(kalman_state_matrix *state, float z_0_laser, float z_0_sonar) {
    /*if(z_0_sonar->valid && z_0_laser->valid) {
        //Calculate the difference between the readings and determine if we are close to a window
        float diff = l_val - s_val;
        if(diff > WINDOW_RECON_THRESHOLD) {
            state->x_k = s_val;
            return;
        }

        calibrate_open_space(state, z_0_laser, z_0_sonar);
    }
    //The range of sonar and laser are the same, but sonar is invalid. We can do nothing but trust the laser
    else if (!z_0_sonar->valid && z_0_laser->valid) {
        state->x_k = l_val;
    }
    //Drone is most likely facing a window - trust the sonar
    else if (z_0_sonar->valid && !z_0_laser->valid) {
        state->x_k = s_val;
    }
    //Drone probably faces an open space
    else {
        calibrate_open_space(state, z_0_laser, z_0_sonar);
    }*/
    calibrate_open_space(state, z_0_laser, z_0_sonar);
}

void calibrate_open_space(kalman_state_matrix *state, float z_0_laser, float z_0_sonar){
    //Declare variables for average variance of sensors, readings and a flag to indicate if the calibration is done.
    float diff = 0;
    uint8_t calibrated = 0;
    float avg = (z_0_laser + z_0_sonar) / 2;
    float r_avg = 0;

    int i, j;
    for (i = 0; i < DATAFUSION_UNITS; ++i) {
        for (j = 0; j < DATAFUSION_UNITS; ++j) {
            r_avg += state->R->values[i][j];
        }
    }
    r_avg = r_avg / (2 * DATAFUSION_UNITS);

    //Run the filter until the value is lower than the average variance.
    while(!calibrated) {
        kalman_datafusion_filter(state, z_0_laser, z_0_sonar);

        diff = abs(avg - state->x_k);
        if(diff <= r_avg)
            calibrated = 1;
    }
}