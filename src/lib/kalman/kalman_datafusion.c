#include "kalman_datafusion.h"

kalman_state_matrix *kalman_datafusion_init (fix16_t a, fix16_t b, log_sender component,
                             matrix_t* C, matrix_t* R)
{
    kalman_state_matrix *state = malloc(sizeof(kalman_state_matrix));
    //Not enough heap-space, abort flight.
    if(!state)
        ERROR("Failed to malloc space for the datafusion-matrix");

    state->source_components = component;
    state->a = a;
    state->b = b;
    state->p_k = fix16_from_int(10);
    state->u_k = fix16_from_int(1);

    //Initialize G_k
    state->G_k = matrix_constructor(1, 2);
    matrix_set(state->G_k, 0, 0, fix16_from_int(1));
    matrix_set(state->G_k, 0, 1, fix16_from_int(1));

    //Initialize and fill C and R
    if(C)
        state->C = C;
    else {
        state->C = matrix_constructor(DATAFUSION_UNITS, 1);
        matrix_set(state->C, 0, 0, fix16_from_int(1));
        matrix_set(state->C, 1, 0, fix16_from_int(1));
    }
    if(R)
        state->R = R;
    else {
        state->R = matrix_constructor(DATAFUSION_UNITS, DATAFUSION_UNITS);
        matrix_set(state->R, 0, 0, fix16_from_int(1));
        matrix_set(state->R, 0, 1, fix16_from_int(0));
        matrix_set(state->R, 1, 0, fix16_from_int(0));
        matrix_set(state->R, 1, 1, fix16_from_int(1));
    }

    //Initialize z_k
    state->z_k = matrix_constructor(2, 1);

    return state;
}

void kalman_datafusion_predict(kalman_state_matrix *state) {
    //x_k = a * x_k + b * u_k (predict the next state from the previous and the control signal)
    state->x_k = fix16_add(fix16_mul(state->a, state->x_k), fix16_mul(state->b, state->u_k));

    //p_k = a^2 * x_k (calculate the uncertainty)
    state->p_k = fix16_mul(fix16_mul(state->a, state->a), state->x_k);
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
    matrix_t *zCx = sub_vec_vec(state->z_k, Cx);

    //calculate MatrixMatrixMultiply(G, z - C * x)
    matrix_t *mmm = mult_mat_mat(state->G_k, zCx);

    //G_k is 1x2 and z - C * x is 2x1 so mmm is 1x1
    fix16_t res = fix16_add(state->x_k,  matrix_get(mmm, 0, 0));

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
    fix16_t res = fix16_mul (fix16_sub(1, matrix_get(mGC, 0, 0)), state->p_k );

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

void kalman_datafusion_filter(kalman_state_matrix *state, fix16_t z_laser, fix16_t z_sonar) {
    //Update the z-vector with the current readings.
    matrix_set(state->z_k, ZLASER, 0, z_laser);
    matrix_set(state->z_k, ZSONAR, 0, z_sonar);

    //Filter
    kalman_datafusion_predict(state);
    kalman_datafusion_update(state);
}

void kalman_datafusion_calibrate(kalman_state_matrix *state, fix16_t z_0_laser, fix16_t z_0_sonar) {
    //Declare variables for average variance of sensors, readings and a flag to indicate if the calibration is done.
    fix16_t diff;
    uint8_t calibrated = fix16_from_int(0);
    fix16_t avg = fix16_div (fix16_add(z_0_laser, z_0_sonar), fix16_from_int(2));
    fix16_t r_avg = fix16_from_int(0);

    int i, j;
    for (i = 0; i < DATAFUSION_UNITS; ++i) {
        for (j = 0; j < DATAFUSION_UNITS; ++j) {
            r_avg = fix16_add(r_avg, matrix_get(state->R, i, j));
        }
    }
    r_avg = fix16_div(r_avg, fix16_mul(fix16_from_int(2), fix16_from_int(DATAFUSION_UNITS)));

    //Run the filter until the value is lower than the average variance.
    while(!calibrated) {
        kalman_datafusion_filter(state, z_0_laser, z_0_sonar);

        diff = fix16_abs(fix16_sub(avg, state->x_k));
        if(diff <= r_avg)
            calibrated = 1;
    }
}