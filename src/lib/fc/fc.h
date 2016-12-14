#ifndef RAND_FC_H
#define RAND_FC_H

#include <stdint.h>
#include <stdlib.h>
#include "libfixmath/fix16.h"

#include "sonar/sonar.h"
#include "laser/laser.h"
#include "ir/ir.h"
#include "core/log.h"
#include "core/io.h"

typedef struct acceleration_s {
    fix16_t x; // left/right
    fix16_t  y; // forward/backwards
    fix16_t  z; // up/down
} acceleration_t;

typedef struct velocity_s {
    fix16_t  x; // left/right
    fix16_t  y; // forward/backwards
    fix16_t  z; // up/down
} velocity_t;

typedef struct duty_s {
    uint16_t MIN_FC_DUTY;
    uint16_t MID_FC_DUTY;
    uint16_t MAX_FC_DUTY;
} duty_t;

typedef struct fc_s {
    duty_t *duty;
    acceleration_t *acc;
    velocity_t *vel;
    tx_t serial;

    uint16_t deltatime;
    uint16_t yaw;
    uint16_t pitch;
    uint16_t roll;
    uint16_t throttle;
    fix16_t gyro; //Rotation Velocity
} fc_t;

// ms = value of 1 ms
/**
 * Initialize the flight controller
 * @param serial - The serial pin the flight controller is connected to
 * @param ms - The shortes length of the pulse when used with PWM signals
 * @return - A pointer to the allocated flight controller struct
 */
fc_t *init_fc(tx_t serial, uint16_t ms);
/**
 * A destructor for the flight controller, frees all allocated memory and the pointer
 * @param fc - Pointer to a fc_t struct - DO NOT USE THIS AFTER THIS FUNCTION CALL
 */
void clean_fc(fc_t *fc);
/**
 * Arms the flight controller
 * @param fc - Pointer to the flight controller to arm
 */
void set_arm(fc_t *fc);
/**
 * Disarms the flight controller
 * @param fc - Pointer to the flight controller to disarm
 */
void set_disarm(fc_t *fc);

/**
 * Rotate the drone left around its' own axis
 * @param fc - Pointer to the flight controller that controls the drone
 */
void rotate_left(fc_t *fc);
/**
 * Rotate the drone right around its' own axis
 * @param fc - Pointer to the flight controller that controls the drone
 */
void rotate_right(fc_t *fc);
/**
 * Stops rotation around the drone's own axis
 * @param fc - Pointer to the flight controller that controls the drone
 */
void rotate_stop(fc_t *fc);

/**
 * Move the drone left relative to its' own forward
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_left(fc_t *fc);
/**
 * Move the drone right relative to its' own forward
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_right(fc_t *fc);
/**
 * Move the drone forward relative to its' own forward
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_forward(fc_t *fc);
/**
 * Move the drone back relative to its' own forward
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_back(fc_t *fc);

/**
 * Move the drone up, increasing altitude
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_up(fc_t *fc);
/**
 * Move the drone down, decreasing altitude
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_down(fc_t *fc);

/**
 * Stops the drones movement on all axes
 * @param fc - Pointer to the flight controller that controls the drone
 */
void move_stop(fc_t *fc);

acceleration_t fc_read_acceleration(fc_t *fc);

void set_acceleration(fc_t *fc, float, float);

void set_velocity(fc_t *fc, float, float);

void update_velocity(fc_t *fc, acceleration_t *a, float);

#endif //RAND_FC_H
