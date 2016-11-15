//
// Created by Lee on 08/11/2016.
//

#include "positioning.h"
#include "fc.h"
#include "ir.h"
#include "sonar.h"
#include "laser.h"

/* sonar + laser front */
kalman_state_matrix front_state;
kalman_state laser_left_state;
kalman_state laser_right_state;
kalman_state ir_top;
kalman_state ir_bottom;

void positioning_init() {
    kalman_datafusion_init(&front_state, 2, SENDER_SONAR);

    /* initialize datafusion A,B,C  here */

    kalman_init(&laser_left_state, 1, 0 /* change */, SENDER_LASER);
    kalman_init(&laser_right_state, 1, 0 /* change */, SENDER_LASER);
    kalman_init(&ir_bottom, 1, 3 /* change */, SENDER_IR);
    kalman_init(&ir_top, 1, 3 /* change */, SENDER_IR);
}

void check_avoidance() {
    /* updates u_k for all kalman states */
    update_u_k();

    /* do readings + filter */


    /* flying logic (avoidance, turns etc.) */
}

void update_u_k() {
    acceleration_t u_k_update = fc_read_acceleration();

    /* if z is between 0 and 1, then we have a positive acceleration to the left
     * if z is between 1 and 2, then we have a positive acceleration to the right
     * if z is 1, then there is no acceleration */
    if (u_k_update.z > MAX_NEGATIVE_ACCELERATION && u_k_update.z < NO_ACCELERATION) {
        laser_right_state.u_k = -1 * u_k_update.z; // -1 simply to negate u_k_update.z
        laser_left_state.u_k = u_k_update.z;
    } else if (u_k_update.z > NO_ACCELERATION && u_k_update.z < MAX_POSITIVE_ACCELERATION) {
        laser_right_state.u_k = u_k_update.z;
        laser_left_state.u_k = -1 * u_k_update.z; // -1 simply to negate u_k_update.z
    } else if (u_k_update.z == NO_ACCELERATION) {
        laser_left_state.u_k = u_k_update.z;
        laser_right_state.u_k = u_k_update.z;
    }

    /* if y is between 0 and 1, then we have a positive acceleration forward
     * if y is between 1 and 2, then we have a positive acceleration backwards
     * if y is 1, then there is no acceleration */
    if (u_k_update.y > MAX_NEGATIVE_ACCELERATION && u_k_update.y < NO_ACCELERATION)
        front_state.u_k = -1 * u_k_update.y; // -1 simply to negate u_k_update.y
    else if (u_k_update.y > NO_ACCELERATION && u_k_update.y < MAX_POSITIVE_ACCELERATION)
        front_state.u_k = u_k_update.y;
    else if (u_k_update.y == NO_ACCELERATION)
        front_state.u_k = u_k_update.y;

    /* if x is between 0 and 1, then we have a positive acceleration upwards
     * if x is between 1 and 2, then we have a positive acceleration downwards
     * if x is 1, then there is no acceleration */
    if (u_k_update.x > MAX_NEGATIVE_ACCELERATION && u_k_update.x < NO_ACCELERATION) {
        ir_bottom.u_k = -1 * u_k_update.x; // -1 simply to negate u_k_update.x
        ir_top.u_k = u_k_update.x;
    } else if (u_k_update.x > NO_ACCELERATION && u_k_update.x < MAX_POSITIVE_ACCELERATION) {
        ir_bottom.u_k = u_k_update.x;
        ir_top.u_k = -1 * u_k_update.x; // -1 simply to negate u_k_update.x
    } else if (u_k_update.x == NO_ACCELERATION) {
        ir_bottom.u_k = u_k_update.x;
        ir_top.u_k = u_k_update.x;
    }
}
