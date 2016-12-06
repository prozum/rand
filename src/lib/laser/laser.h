#ifndef RAND_LASER_H
#define RAND_LASER_H

#include <stdint.h>
#include <stdlib.h>
#include "core/io.h"

#define LASER_MIN_DISTANCE_M 0.02
#define LASER_MAX_DISTANCE_M 4

typedef struct laser_s {
    tx_t pin; //pin -- maybe not tx_t, I have no idea!
    //latests readings in cm
    uint16_t left_value;
    uint16_t right_value;
    uint16_t front_value;
} laser_t;

laser_t *laser_init(tx_t pin);

void set_laser_values(laser_t *l, float, float, float);

uint16_t laser_read_dist(laser_t *laser);

#endif //RAND_LASER_H


