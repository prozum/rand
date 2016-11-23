#include "laser/laser.h"

uint8_t laser_valid_reading;

laser_t *laser_init(tx_t pin) {
    laser_t *laser = malloc(sizeof(laser_t));

    laser->pin = pin;
    laser->valid = 0;
    laser->left_value = 0;
    laser->right_value = 0;
    laser->front_value = 0;

    return laser;
}