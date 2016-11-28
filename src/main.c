#include "task.h"
#include "sonar/sonar.h"
#include "laser/laser.h"
#include "ir/ir.h"
#include "positioning/positioning.h"

void init_not_timed();

int main ()
{
    init_not_timed();

    // initialize timer dependent tasks
    task_timer_setup();
    task_arm_fc();

    while (1) {
        task_pulse();

        read_sonar(sonar);

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        IR_read(bottom_ir);
        IR_read(top_ir);
        laser_read_dist(laser);

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        //task_calculate_position();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;
    }
}

void init_not_timed() {
    // initialize tasks
    sonar = sonar_init(SONAR_TRIGGER_PIN, SONAR_ECHO_PIN);
    laser = laser_init(USB_RX);
    top_ir = IR_init(IR_TOP_PIN);
    bottom_ir = IR_init(IR_BOTTOM_PIN);
    task_init_fc();
    /*Maybe some error-checking here*/

    float a[SENSOR_FILTERS];
    a[LEFT_READING] = SIDE_a;
    a[RIGHT_READING] = SIDE_a;
    a[TOP_READING] = TOP_BOT_a;
    a[BOTTOM_READING] = TOP_BOT_a;

    float r[SENSOR_FILTERS];
    r[LEFT_READING] = LASER_r;
    r[RIGHT_READING] = LASER_r;
    r[TOP_READING] = IR_r;
    r[BOTTOM_READING] = IR_r;

    float A[DATAFUSION_FILTERS];
    A[FRONT_READING] = FRONT_a;

    float R[DATAFUSION_FILTERS];
    R[FRONT_READING] = LASER_r + SONAR_r / 2;

    recent_position = positioning_init(a, r, A, R);

    read_sonar(sonar);
    IR_read(bottom_ir);
    IR_read(top_ir);
    //laser_read(laser);

    float readings[SENSOR_FILTERS];
    readings[LEFT_READING] = laser->left_value;
    readings[RIGHT_READING] = laser->right_value;
    readings[TOP_READING] = top_ir->value;
    readings[BOTTOM_READING] = bottom_ir->value;

    float df_readings[DATAFUSION_FILTERS];
    df_readings[ZLASER] = laser->front_value;
    df_readings[ZSONAR] = sonar->value;

    positioning_calibrate(recent_position, readings, df_readings);
}

/*
ISR(TIMER1_OVF_vect)
{
    goto schedule_start;
    return;
}
*/