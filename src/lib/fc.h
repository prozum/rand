#ifndef RAND_FC_H
#define RAND_FC_H

#include <stdint.h>

static const uint16_t MIN_FC_PWM = 1000;
static const uint16_t MID_FC_PWM = 1500;
static const uint16_t MAX_FC_PWM = 2000;

void rotate_z_axis(uint16_t angle);

void move_x_axis(int8_t d);

void move_y_axis(int8_t d);

void move_z_axis(int8_t d);

#endif //RAND_FC_H
