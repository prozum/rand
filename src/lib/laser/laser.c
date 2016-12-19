#include "laser/laser.h"

void laser_init(laser_t *laser, tx_t pin) {
    laser->pin = pin;
    laser->val_left = 0;
    laser->val_right = 0;
    laser->val_front = 0;
}

void laser_read_dist(laser_t *laser) {
    uint16_t res = 0;
    const uint8_t INPUT_SIZE = 4;

    char *input = serial_read_string_nowait(TX1, INPUT_SIZE);

    for (uint8_t i = 0; i < INPUT_SIZE; i++) {
        res += input[i] << (INPUT_SIZE - (i + 1));
    }

    laser->val_front = res;
}