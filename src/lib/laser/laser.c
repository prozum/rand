#include "laser/laser.h"

laser_t *laser_init(tx_t pin) {
    laser_t *laser = malloc(sizeof(laser_t));

    laser->pin = pin;
    laser->valid = 0;
    laser->left_value = 0;
    laser->right_value = 0;
    laser->front_value = 0;

    return laser;
}

uint16_t laser_read_dist(laser_t *laser)
{
    laser->front_value = atoi(serial_read_string_nowait(SERIAL0, 4));

    if (laser->front_value == 0) {
        laser->valid = 0;
    } else  {
        laser->valid = 1;
    }
}