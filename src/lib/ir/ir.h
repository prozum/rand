#ifndef RAND_IR_H
#define RAND_IR_H

/** @file ir.h
 * \brief Infrared sensor functions and data
 *
 * \addtogroup SensorInfrared
 * @{
 */

#include <math.h>
#include "core/io.h"
#include "kalman/kalman.h"

//! The IR is placed on an 8-bit pin
#define IR_MAX_DIST_CM 80
#define IR_MIN_DIST_CM 0

typedef struct ir_s {
    apin_t pin;    //!< Receive pin
    uint8_t value; //!< Latest reading in cm
} ir_t;

/**
 * Initialize an ir_t struct on the specified pin
 * @param ir - A pointer to the ir_t struct that represents the infrared sensor
 * @param pin - The pin to read infrared values from
 */
void ir_init(ir_t *ir, apin_t pin);
/**
 * Reads a value from the ir specified by the pointer
 * @param ir - A pointer to the ir_t struct that represents the infrared sensor
 * @return - The value read by the sensor
 */
uint16_t ir_read(ir_t *ir);

#endif //RAND_IR_H

//! @}
