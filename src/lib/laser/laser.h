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

#define LASER_MAX_DISTANCE_CM 2200

typedef struct laser_s {
    tx_t pin; //!< Pin -- maybe not tx_t, I have no idea!
    //! Latests readings in cm
    uint16_t val_left;
    uint16_t val_right;
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

#endif //RAND_LASER_H

//! @}
