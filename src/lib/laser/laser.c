#include "laser/laser.h"

laser_t *laser_init(tx_t pin) {
    laser_t *laser = malloc(sizeof(laser_t));

    laser->pin = pin;
    laser->val_left = 0;
    laser->val_right = 0;
    laser->front_value = 0;

    return laser;
}

void set_laser_values(laser_t *laser, float left, float right, float front){
    laser->val_left = left;
    laser->val_right = right;
    laser->front_value = front;
}


void laser_read_dist(laser_t *laser)
{
    uint16_t res = 0;
    const uint8_t INPUT_SIZE = 4;

    char *input = serial_read_string_nowait(TX1, INPUT_SIZE);

    for(uint8_t i = 0; i < INPUT_SIZE; i++) {
        res += input[i] << (INPUT_SIZE - (i + 1));
    }

    laser->front_value = res;
}