#ifndef RAND_FC_H
#define RAND_FC_H

#include <stdint.h>
#include <stdlib.h>

#include "sonar/sonar.h"
#include "laser/laser.h"
#include "ir/ir.h"
#include "core/log.h"
#include "core/io.h"

typedef struct acceleration_s {
    float x; // left/right
    float y; // forward/backwards
    float z; // up/down
} acceleration_t;

typedef struct velocity_s {
    float x; // left/right
    float y; // forward/backwards
    float z; // up/down
} velocity_t;

typedef struct duty_s {
    uint16_t MIN_FC_DUTY;
    uint16_t MID_FC_DUTY;
    uint16_t MAX_FC_DUTY;
} duty_t;

typedef struct fc_s {
    duty_t *duty;
    acceleration_t *acc;
    velocity_t *vel;
    serial_t serial;

    uint16_t deltatime;
    uint16_t yaw;
    uint16_t pitch;
    uint16_t roll;
    uint16_t throttle;
} fc_t;

// ms = value of 1 ms
void init_fc(fc_t *fc, serial_t serial, uint16_t ms);
void clean_fc(fc_t *fc);
void set_arm(fc_t *fc);
void set_disarm(fc_t *fc);

void rotate_left(fc_t *fc);

void rotate_right(fc_t *fc);

void rotate_stop(fc_t *fc);

void move_left(fc_t *fc);

void move_right(fc_t *fc);

void move_forward(fc_t *fc);

void move_back(fc_t *fc);

void move_up(fc_t *fc);

void move_down(fc_t *fc);

void move_stop(fc_t *fc);

acceleration_t fc_read_acceleration(fc_t *fc);

void set_acceleration(fc_t *fc, float, float);

void set_velocity(fc_t *fc, float, float);

void update_velocity(fc_t *fc, acceleration_t *a, float);

#endif //RAND_FC_H
