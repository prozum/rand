#ifndef RAND_IR_H
#define RAND_IR_H

#include <math.h>


#include "core/io.h"
#include "kalman/kalman.h"

//The IR is placed on an 8-bit pin
#define IR_MAX_INPUT 255

typedef struct ir_s {
    apin_t pin;    // receive pin
    uint8_t value; // latest reading in cm
} ir_t;

ir_t *IR_init(apin_t pin);

uint16_t IR_read(ir_t *ir);

/*
float IR_top_to_meters();

float IR_bottom_to_meters();
*/

void IR_calibrate(float z_0);

#endif //RAND_IR_H
