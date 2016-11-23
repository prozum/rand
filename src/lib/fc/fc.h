#ifndef RAND_FC_H
#define RAND_FC_H

#include <stdint.h>

typedef struct acceleration_s { /* between 0-1 negative acceleration, between 1-2 positive acceleration */
    // positive(1-2)/negative(0-1)
    float x; // up/down
    float y; // forward/backwards
    float z; // left/right
} acceleration_t;

uint16_t yaw;
uint16_t pitch;
uint16_t roll;
uint16_t throttle;

static uint16_t MIN_FC_DUTY;
static uint16_t MID_FC_DUTY;
static uint16_t MAX_FC_DUTY;

// ms = value of 1 ms
void init_fc(uint16_t ms);

void reset();

void set_arm();
void set_disarm();

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

acceleration_t fc_read_acceleration();

#endif //RAND_FC_H
