#ifndef RAND_FC_H
#define RAND_FC_H

#include <stdint.h>

const uint16_t MIN_FC_DUTY = 1250;
const uint16_t MID_FC_DUTY = 1500;
const uint16_t MAX_FC_DUTY = 1750;

// low, medium and high stick positions
static const uint16_t STICK_L = 1000;
static const uint16_t STICK_M = 1500;
static const uint16_t STICK_H = 2000;

static void set_yaw(uint16_t d);
static void set_pitch(uint16_t d);
static void set_roll(uint16_t d);
static void set_throttle(uint16_t d);

void init_fc();
void arm_fc();
void disarm_fc();

void rotate_left();
void rotate_right();
void rotate_stop();

void move_left();
void move_right();
void move_forward();
void move_back();
void move_up();
void move_down();
void move_stop();

#endif //RAND_FC_H
