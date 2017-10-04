#ifndef RAND_LASER_H
#define RAND_LASER_H

/** @file laser.h
 * \brief Laser sensor functions and data
 *
 * \addtogroup SensorLaser
 * @{
 */

#include <stdint.h>
#include <stdlib.h>

#include "core/io.h"

#define LASER_MAX_DISTANCE_CM 2200 //!< Defines the maximum reading-distance for the laser module

/**
 * The data-structure for the laser module
 */
typedef struct laser_s {
    tx_t pin; //!< Pin -- maybe not tx_t, I have no idea!
    //! Latests reading to the left in cm
    uint16_t val_left;
    //! Latests reading to the right in cm
    uint16_t val_right;
    //! Latests reading in front of the drone in cm
    uint16_t val_front;
} laser_t;

/**
 * Initializes a laser-struct
 * @param laser - A pointer to the laser-struct to init
 * @param pin - The pin to read laser-values from
 */
void laser_init(laser_t *laser, tx_t pin);

/**
 * Read values from the laser
 * @param laser - A pointer to the laser-struct to read from
 */
void laser_read_dist(laser_t *laser);

#endif // RAND_LASER_H

//! @}
