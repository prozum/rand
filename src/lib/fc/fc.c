#include "fc/fc.h"

void init_fc(uint16_t ms)
{
    MIN_FC_DUTY = ms;
    MID_FC_DUTY = (ms * 1.5);
    MAX_FC_DUTY = (ms * 2);
}

void set_arm()
{
    yaw = MAX_FC_DUTY;
    throttle = MIN_FC_DUTY;
    pitch = MID_FC_DUTY;
    roll = MID_FC_DUTY;
}

void set_disarm()
{
    yaw = MIN_FC_DUTY;
    throttle = MIN_FC_DUTY;
    pitch = MID_FC_DUTY;
    roll = MID_FC_DUTY;
}

void rotate_left()
{
    yaw = MIN_FC_DUTY;
}

void rotate_right()
{
    yaw = MAX_FC_DUTY;
}

void rotate_stop()
{
    yaw = MID_FC_DUTY;
}

void move_left()
{
    roll = MIN_FC_DUTY;
}

void move_right()
{
    roll = MAX_FC_DUTY;
}

void move_forward()
{
    pitch = MAX_FC_DUTY;
}

void move_back()
{
    pitch = MIN_FC_DUTY;
}

void move_up()
{
    throttle = MAX_FC_DUTY;
}

void move_down()
{
    throttle = MIN_FC_DUTY;
}

void move_stop()
{
    throttle = MID_FC_DUTY;
    pitch = MID_FC_DUTY;
    roll = MID_FC_DUTY;
    yaw = MID_FC_DUTY;
}