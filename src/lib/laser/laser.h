#ifndef RAND_LASER_H
#define RAND_LASER_H

#include <stdint.h>
#include <stdlib.h>
#include "core/io.h"

#define LASER_MAX_DISTANCE_CM 2200

typedef struct laser_s {
    tx_t pin; //pin -- maybe not tx_t, I have no idea!
    //latests readings in cm
    uint16_t val_left;
    uint16_t val_right;
    uint16_t val_front;
} laser_t;

laser_t *laser_init(tx_t pin);

void set_laser_values(laser_t *l, float, float, float);

void laser_read_dist(laser_t *laser);

#endif //RAND_LASER_H


