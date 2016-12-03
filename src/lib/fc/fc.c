#include "fc/fc.h"
#include <core/m328p.h>

void init_fc(fc_t *fc, serial_t serial, uint16_t ms)
{
    fc->acc = (acceleration_t *)malloc(sizeof(acceleration_t));
    fc->duty = (duty_t *)malloc(sizeof(duty_t));
    fc->serial = serial;

    fc->duty->MIN_FC_DUTY = ms;
    fc->duty->MID_FC_DUTY = (uint16_t)(ms * 1.5);
    fc->duty->MAX_FC_DUTY = (uint16_t)(ms * 2);
}

void clean_fc(fc_t *fc)
{
    free(fc->acc);
    free(fc->duty);
    free(fc);
}

void set_arm(fc_t *fc)
{
    fc->yaw = fc->duty->MAX_FC_DUTY;
    fc->throttle = fc->duty->MIN_FC_DUTY;
    fc->pitch = fc->duty->MID_FC_DUTY;
    fc->roll = fc->duty->MID_FC_DUTY;
}

void set_disarm(fc_t *fc)
{
    fc->yaw = fc->duty->MIN_FC_DUTY;
    fc->throttle = fc->duty->MIN_FC_DUTY;
    fc->pitch = fc->duty->MID_FC_DUTY;
    fc->roll = fc->duty->MID_FC_DUTY;
}

void rotate_left(fc_t *fc)
{
    fc->yaw = fc->duty->MIN_FC_DUTY;
}

void rotate_right(fc_t *fc)
{
    fc->yaw = fc->duty->MAX_FC_DUTY;
}

void rotate_stop(fc_t *fc)
{
    fc->yaw = fc->duty->MID_FC_DUTY;
}

void move_left(fc_t *fc)
{
    fc->roll = fc->duty->MIN_FC_DUTY;
}

void move_right(fc_t *fc)
{
    fc->roll = fc->duty->MAX_FC_DUTY;
}

void move_forward(fc_t *fc)
{
    fc->pitch = fc->duty->MAX_FC_DUTY;
}

void move_back(fc_t *fc)
{
    fc->pitch = fc->duty->MIN_FC_DUTY;
}

void move_up(fc_t *fc)
{
    fc->throttle = fc->duty->MAX_FC_DUTY;
}

void move_down(fc_t *fc)
{
    fc->throttle = fc->duty->MIN_FC_DUTY;
}

void move_stop(fc_t *fc)
{
    fc->throttle = fc->duty->MID_FC_DUTY;
    fc->pitch = fc->duty->MID_FC_DUTY;
    fc->roll = fc->duty->MID_FC_DUTY;
    fc->yaw = fc->duty->MID_FC_DUTY;
}

void set_acceleration(fc_t *fc, float x, float y){
    fc->acc->y = y;
    fc->acc->x = x;
}

void set_velocity(fc_t *fc, float x, float y){
    fc->vel->y = y;
    fc->vel->x = x;
}

//Assumed that time is in seconds.
void update_velocity(fc_t *fc, acceleration_t *a, float time){
    fc->vel->x = fc->vel->x + a->x * time;
    fc->vel->y = fc->vel->y + a->y * time;
}

acceleration_t fc_read_acceleration(fc_t *fc) {
    ERROR("This function is not supported yet.");

    acceleration_t accel = {0, 0.5, 0};
    return accel;
}