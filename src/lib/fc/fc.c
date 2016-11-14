#include "fc/fc.h"

/* private interface */
static void set_yaw(uint16_t d) {

}

static void set_pitch(uint16_t d) {

}

static void set_roll(uint16_t d) {

}

static void set_throttle(uint16_t d) {

}

void init_fc() {

}

// when pitch and roll are set to medium,
// throttle is set to low and yaw is set to high
// then the naze32 is armed
void arm_fc() {
    set_pitch(STICK_M);
    set_roll(STICK_M);
    set_throttle(STICK_L);
    set_yaw(STICK_H);
}

// when pitch and roll are set to medium,
// throttle is set to low and yaw is set to low
// then the naze32 is disarmed
void disarm_fc() {
    set_pitch(STICK_M);
    set_roll(STICK_M);
    set_throttle(STICK_L);
    set_yaw(STICK_L);
}

void rotate_left() {
    set_yaw(MIN_FC_DUTY);
}

void rotate_right() {
    set_yaw(MAX_FC_DUTY);
}

void rotate_stop() {
    set_yaw(MID_FC_DUTY);
}

void move_left() {
    set_roll(MIN_FC_DUTY);
}

void move_right() {
    set_roll(MAX_FC_DUTY);
}

void move_forward() {
    set_pitch(MAX_FC_DUTY);
}

void move_back() {
    set_pitch(MIN_FC_DUTY);
}

void move_up() {
    set_throttle(MAX_FC_DUTY);
}

void move_down() {
    set_throttle(MIN_FC_DUTY);
}

void move_stop() {
    set_throttle(MID_FC_DUTY);
    set_pitch(MID_FC_DUTY);
    set_yaw(MID_FC_DUTY);
}