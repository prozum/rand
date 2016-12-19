#ifndef RAND_FC_H
#define RAND_FC_H

/** @file fc.h
 * \brief Flight controller functions and data
 *
 * \addtogroup FlightController
 * @{
 */

#include <stdint.h>
#include <stdlib.h>
#include "libfixmath/fix16.h"

#include "sonar/sonar.h"
#include "laser/laser.h"
#include "ir/ir.h"
#include "core/log.h"
#include "core/io.h"
/**
 * A struct for containing acceleration-values read by the Naze32 Rev6 flight-controller
 */
typedef struct acceleration_s {
    fix16_t x;  //!< Left/right
    fix16_t  y; //!< Forward/backwards
    fix16_t  z; //!< Up/down
} acceleration_t;

/**
 * A struct for containing velocity-values read by the Naze32 Rev 6 flight-controller
 */
typedef struct velocity_s {
    fix16_t  x; //!< Left/right
    fix16_t  y; //!< Forward/backwards
    fix16_t  z; //!< Up/down
} velocity_t;

/**
 * Defines the possible duty cycles used to control the flight-controller
 */
typedef struct duty_s {
    uint16_t MIN_FC_DUTY; //!< Minimum value, i.e. full backwards speed on the given axis
    uint16_t MID_FC_DUTY; //!< Mid value, i.e. no speed on the given axis
    uint16_t MAX_FC_DUTY; //!< Maximum value, i.e. full speed ahead on the given axis
} duty_t;

/**
 * A data-structure for storing data related to the implementation of the flight-controller
 */
typedef struct fc_s {
    duty_t *duty; //!< Stores the desired duty-values
    acceleration_t *acc; //!< Stores the readings from the flight-controllers accelerometer
    velocity_t *vel; //!< Stores the accumulated velocity
    tx_t serial; //!< Stores the serial pin to which the flight-controller is connected

    uint16_t deltatime; //!< Stores the time since the flight-controller was last scheduled
    uint16_t yaw; //!< Stores the current duty-value for the yaw-axis (rotation around the vertical axis)
    uint16_t pitch; //!< Stores the current duty-value for the pitch-axis (forwards/backwards)
    uint16_t roll; //!< Stores the current duty-value for the roll-axis (left/right)
    uint16_t throttle; //!< Stores the current duty-value for the throttle-axis (up/down)
    fix16_t gyro; //!< Rotation Velocity
} fc_t;

/**
 * Initialize the flight controller
 * @param fc - Pointer to the flight controller to init
 * @param serial - The serial pin the flight controller is connected to
 * @param ms - The shortes length of the pulse when used with PWM signals
 */
void init_fc(fc_t *fc, tx_t serial, uint16_t ms);
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

/**
 * Reads the acceleration from the flight-controller
 * @param fc - A pointer to the fc_t struct that represents the physical flight-controller
 * @return - The latest acceleration reading
 */
acceleration_t fc_read_acceleration(fc_t *fc);

/**
 * Sets the acceleration of the flight-controller (only for debugging purpose)
 * @param fc - A pointer to the fc_t struct that represents the physical flight-controller
 * @param x - The acceleration in the x-axis (left/right)
 * @param y - The acceleration in the y-axis (forwards/backwards)
 * @param z - The acceleration in the z-axis (up/down)
 */
void set_acceleration(fc_t *fc, float x, float y, float z);

/**
 * Sets the velocity of the flight-controller (only for debugging purpose)
 * @param fc - A pointer to the fc_t struct that represents the physical flight-controller
 * @param x - The velocity in the x-axis (left/right)
 * @param y - The velocity in the y-axis (forwards/backwards)
 * @param z - The velocity in the z-axis (up/down)
 */
void set_velocity(fc_t *fc, float x, float y, float z);

/**
 * Calculates the velocity by accumulating the acceleration over the delta-time
 * @param fc - A pointer to the fc_t struct that represents the physical flight-controller
 * @param a - A pointer to an acceleration struct with the current acceleration
 * @param deltatime - The time since the last call to the function
 */
void update_velocity(fc_t *fc, acceleration_t *a, float deltatime);

#endif //RAND_FC_H

//! @}