#ifndef RAND_IR_H
#define RAND_IR_H

#include <math.h>
#include "core/io.h"
#include "kalman/kalman.h"

//The IR is placed on an 8-bit pin
#define IR_MAX_DIST_CM 80
#define IR_MIN_DIST_CM 0

typedef struct ir_s {
    apin_t pin;    // receive pin
    uint8_t value; // latest reading in cm
} ir_t;

/**
 * Initialize an ir_t struct on the specified pin
 * @param pin - The pin to read infrared values from
 * @return - A pointer to the allocated struct
 */
ir_t *IR_init(apin_t pin);
/**
 * Reads a value from the ir specified by the pointer
 * @param ir - A pointer to the ir_t struct that represents the infrared sensor
 * @return - The value read by the sensor
 */
uint16_t ir_read(ir_t *ir);
#endif //RAND_IR_H
