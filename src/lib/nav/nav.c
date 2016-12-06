#include "nav.h"

position_t *positioning_init(float a[SENSOR_FILTERS], float r[SENSOR_FILTERS],
                             float A[DATAFUSION_FILTERS], float B[DATAFUSION_FILTERS]) {
    int i = 0;
    for (i; i < SENSOR_FILTERS; ++i) {
        kalman_filters[i] = kalman_init(a[i], r[i], SENDER_BOARD);
    }
    i = 0;
    for (i; i < DATAFUSION_FILTERS; ++i) {
        /*todo: FIND A BETTER SOLUTION!*/
        float C[2][2] = {{1, 0}, {1, 0}};
        float R[2][2] = {{1, 0}, {0, 1}};

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

/**
 * This function is called by the scheduler for every
 */
void navigation(rep_t *rep, nav_t *nav){
    /* this should stop the drone if there's less or equal to 120 cm forward */
    if ( (rep->sonar->valid) == 1 && (rep->sonar->value <= MIN_RANGE || rep->laser->front_value <= MIN_RANGE))
        move_stop(rep->fc);
    
    
}

void init_rep(fc_t *fc, laser_t *laser, sonar_t *sonar, ir_t *irTop, ir_t *irBottom, rep_t *rep){
    rep->fc = fc;
    rep->laser = laser;
    rep->sonar = sonar;
    rep->ir_top = irTop;
    rep->ir_bottom = irBottom;
}

/**
 * Takes in the newest measured data.
 * @return the updated representation struct
 *
rep_t update(rep_t *rep){
    rep_t rep;
    rep.fc = rep->fc;
    rep.laser = rep->laser;
    rep.sonar = sonar;
    rep.ir_top = ir_top;
    rep.ir_bottom = ir_bottom;

    return rep;
}*/

uint8_t CheckAWallF(rep_t *rep){
    if((rep->sonar->valid) == 1 && (rep->sonar->value <= 40 || rep->laser->front_value <= 40)){
        return 1;
    }
    return 0;
}

uint8_t CheckAWallL(rep_t *rep) {
    //Check map
    if (rep->laser->left_value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWallR(rep_t *rep) {
    //Check map
    if (rep->laser->right_value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAGround(rep_t *rep) {
    if (rep->ir_bottom->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckACeiling(rep_t *rep) {
    if (rep->ir_top->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinF(rep_t *rep) {
    if (rep->sonar->valid && rep->laser->left_value >= 60 && rep->sonar->value <= 40) {
        return 1;
    }
    return 0;
}

uint8_t CheckAWinL(rep_t *rep) {
    if (rep->laser->left_value >= 40) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

uint8_t CheckAWinR(rep_t *rep) {
    if (rep->laser->right_value >= 40) {
        //Cross reference map and turn to check with sonar if necessary
    }
    return 0;
}

void update_state(state_t *state, rep_t *rep){
    state->ACeiling = CheckAWCeiling(&rep);
    state->AGround =  CheckAGround(&rep);
    state->AWallF = CheckAWallF(&rep);
    state->AWallL = CheckAWallL(&rep);
    state->AWallR = CheckAWallR(&rep);
    state->AWinF = CheckAWinF(&rep);
    state->AWinL = CheckAWinL(&rep);
    state->AWinR = CheckAWinR(&rep);
}



