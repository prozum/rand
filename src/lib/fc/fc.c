#include "fc/fc.h"

void init_fc(fc_t *fc, tx_t serial, uint16_t ms)
{
    fc->acc = (acceleration_t *)malloc(sizeof(acceleration_t));
    fc->vel = (velocity_t *) malloc(sizeof(velocity_t));
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

void set_acceleration(fc_t *fc, float x, float y, float z){
    fc->acc->y = fix16_from_float(y);
    fc->acc->x = fix16_from_float(x);
    fc->acc->z = fix16_from_float(z);
}

void set_velocity(fc_t *fc, float x, float y, float z){
    fc->vel->y = fix16_from_float(y);
    fc->vel->x = fix16_from_float(x);
    fc->acc->z = fix16_from_float(z);
}

//Assumed that time is in seconds.
void update_velocity(fc_t *fc, acceleration_t *a, float deltatime){
    fc->vel->x = fix16_add(fc->vel->x, fix16_mul(a->x, fix16_from_float(deltatime)));
    fc->vel->y = fix16_add(fc->vel->y, fix16_mul(a->y, fix16_from_float(deltatime)));
    fc->vel->z = fix16_add(fc->vel->z, fix16_mul(a->z, fix16_from_float(deltatime)));
}

acceleration_t fc_read_acceleration(fc_t *fc) {
    ERROR("This function is not supported yet.");

    acceleration_t accel = {fix16_from_float(0),
                            fix16_from_float(0.5),
                            fix16_from_float(0)};
    return accel;
}