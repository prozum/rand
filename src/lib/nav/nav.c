#include "nav.h"

position_t *positioning_init(float a[SENSOR_FILTERS], float r[SENSOR_FILTERS],
                             float A[DATAFUSION_FILTERS], float B[DATAFUSION_FILTERS]) {
    int i = 0;
    for (i; i < SENSOR_FILTERS; ++i) {
        kalman_filters[i] = kalman_init(a[i], r[i], SENDER_BOARD);
    }
    i = 0;
    for (i; i < DATAFUSION_FILTERS; ++i) {
        matrix_t *C = matrix_constructor(2, 1);
        matrix_set(C, 0, 0, 1);
        matrix_set(C, 1, 0, 1);

        matrix_t *R = matrix_constructor(2, 2);
        matrix_set(R, 0, 0, 1);
        matrix_set(R, 0, 1, 0);
        matrix_set(R, 1, 0, 0);
        matrix_set(R, 1, 1, 1);

        datafusion_filters[i] = kalman_datafusion_init(A[i], B[DATAFUSION_FILTERS], SENDER_BOARD, C, R);
    }

    position_t *position = malloc(sizeof(position_t));
    if(!position)
        ERROR("Failed to allocate space for position field.");

    return position;
}

void positioning_calibrate(position_t *position, float sensor_initial_readings[SENSOR_FILTERS],
                           float df_init_readings[2 * SENSOR_FILTERS]) {
    int i = 0;
    for (i; i < DATAFUSION_FILTERS; ++i) {
        kalman_datafusion_calibrate(datafusion_filters[i], df_init_readings[2*i], df_init_readings[2*i + 1]);
    }

    i = 0;
    for (i; i < SENSOR_FILTERS; ++i) {
        kalman_calibrate(kalman_filters[i], sensor_initial_readings[i]);
    }

    positioning_calculate(position, sensor_initial_readings, df_init_readings);
}

void positioning_calculate(position_t *position, float sensor_readings[SENSOR_FILTERS],
                           float df_readings[DATAFUSION_FILTERS * 2]) {

    //recent_position = calculated_position; something like this
}

void update_u_k() {
    ERROR("This function is not implemented yet.");

//    acceleration_t u_k_update = fc_read_acceleration();

    /* if z is between 0 and 1, then we have a positive acceleration to the left
     * if z is between 1 and 2, then we have a positive acceleration to the right
     * if z is 1, then there is no acceleration */
/*    if (u_k_update.z > MAX_NEGATIVE_ACCELERATION && u_k_update.z < NO_ACCELERATION) {
        laser_right_state.u_k = -1 * u_k_update.z; // -1 simply to negate u_k_update.z
        laser_left_state.u_k = u_k_update.z;
    } else if (u_k_update.z > NO_ACCELERATION && u_k_update.z < MAX_POSITIVE_ACCELERATION) {
        laser_right_state.u_k = u_k_update.z;
        laser_left_state.u_k = -1 * u_k_update.z; // -1 simply to negate u_k_update.z
    } else if (u_k_update.z == NO_ACCELERATION) {
        laser_left_state.u_k = u_k_update.z;
        laser_right_state.u_k = u_k_update.z;
    }*/

    /* if y is between 0 and 1, then we have a positive acceleration forward
     * if y is between 1 and 2, then we have a positive acceleration backwards
     * if y is 1, then there is no acceleration */
/*    if (u_k_update.y > MAX_NEGATIVE_ACCELERATION && u_k_update.y < NO_ACCELERATION)
        front_state.u_k = -1 * u_k_update.y; // -1 simply to negate u_k_update.y
    else if (u_k_update.y > NO_ACCELERATION && u_k_update.y < MAX_POSITIVE_ACCELERATION)
        front_state.u_k = u_k_update.y;
    else if (u_k_update.y == NO_ACCELERATION)
        front_state.u_k = u_k_update.y;*/

    /* if x is between 0 and 1, then we have a positive acceleration upwards
     * if x is between 1 and 2, then we have a positive acceleration downwards
     * if x is 1, then there is no acceleration */
/*    if (u_k_update.x > MAX_NEGATIVE_ACCELERATION && u_k_update.x < NO_ACCELERATION) {
        ir_bottom.u_k = -1 * u_k_update.x; // -1 simply to negate u_k_update.x
        ir_top.u_k = u_k_update.x;
    } else if (u_k_update.x > NO_ACCELERATION && u_k_update.x < MAX_POSITIVE_ACCELERATION) {
        ir_bottom.u_k = u_k_update.x;
        ir_top.u_k = -1 * u_k_update.x; // -1 simply to negate u_k_update.x
    } else if (u_k_update.x == NO_ACCELERATION) {
        ir_bottom.u_k = u_k_update.x;
        ir_top.u_k = u_k_update.x;
    }*/
}

void navigation(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *ir_top, ir_t *ir_bottom)
{
    /* this should stop the drone if there's less or equal to 120 cm forward */
    if ( (sonar->valid) == 1 && (sonar->value <= 120 || laser->front_value <= 120))
        move_stop(fc);
    
    
}
