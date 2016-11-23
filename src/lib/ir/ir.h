#ifndef RAND_IR_H
#define RAND_IR_H

#include <math.h>


#include "core/io.h"
#include "kalman/kalman.h"

//The IR is placed on an 8-bit pin
#define IR_MAX_INPUT 255

typedef struct ir_s {
    apin_t pin;
    uint8_t value;
} ir_t;

ir_t *IR_init(apin_t pin);

void IR_read(ir_t *ir);

#endif //RAND_IR_H
