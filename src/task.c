#include "task.h"

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
}

void task_timer_setup()
{
    // disable interrupts
    cli();

    // reset all timer flags
    TCCR1A = 0;
    TCCR1B = 0;

    // set prescaler of 256
    TCCR1B |= (1 << CS12);
    ICR1 = OVERFLOW;

    // enable interrupts
    sei();
}

void task_init_fc()
{
    init_fc(fc, SERIAL0, ONE_MS);

    set_pin_mode(YAW, OUTPUT);
    set_pin_mode(ROLL, OUTPUT);
    set_pin_mode(PITCH, OUTPUT);
    set_pin_mode(THROTTLE, OUTPUT);
}

void task_arm_fc()
{
    set_arm(fc);

    int i;

    for (i = 0; i < 20; ++i) {

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;
    }
}

void task_disarm_fc()
{
    set_disarm(fc);

    int i;

    for (i = 0; i < 20; ++i) {

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;
    }
}

void task_pulse()
{
    digital_write(YAW, HIGH);
    digital_write(ROLL, HIGH);
    digital_write(PITCH, HIGH);
    digital_write(THROTTLE, HIGH);

    while (TCNT1 <= ONE_MS);

    if(fc->yaw == ONE_MS)
        digital_write(YAW, LOW);

    if(fc->roll == ONE_MS)
        digital_write(ROLL, LOW);

    if(fc->pitch == ONE_MS)
        digital_write(PITCH, LOW);

    if(fc->throttle == ONE_MS)
        digital_write(THROTTLE, LOW);

    //This loop MUST be below line 80
    while (TCNT1 <= ONE_AND_A_HALF_MS);

    if(fc->yaw == ONE_AND_A_HALF_MS)
        digital_write(YAW, LOW);

    if(fc->roll == ONE_AND_A_HALF_MS)
        digital_write(ROLL, LOW);

    if(fc->pitch == ONE_AND_A_HALF_MS)
        digital_write(PITCH, LOW);

    if(fc->throttle == ONE_AND_A_HALF_MS)
        digital_write(THROTTLE, LOW);

    while (TCNT1 <= TWO_MS);

    if(fc->yaw == TWO_MS)
        digital_write(YAW, LOW);

    if(fc->roll == TWO_MS)
        digital_write(ROLL, LOW);

    if(fc->pitch == TWO_MS)
        digital_write(PITCH, LOW);

    if(fc->throttle == TWO_MS)
        digital_write(THROTTLE, LOW);
}

void task_navigation()
{

}

void task_read_laser()
{
    laser_read_dist(laser);
}

void task_read_ir()
{
    IR_read(bottom_ir);
    IR_read(top_ir);
}

void task_read_sonar()
{
    sonar->valid = 0;

    uint16_t start, stop;
    uint16_t next_ping = TCNT1 + TWO_MS;

    //Ping and LOW-HIGH-LOW with 2 milis delay in-between
    sonar_ping (sonar, LOW);
    while(TCNT1 < next_ping);

    next_ping = TCNT1 + TWO_MS;
    sonar_ping(sonar, HIGH);

    while(TCNT1 < next_ping);
    sonar_ping(sonar, LOW);

    //Start timer and read sonar and stop timer
    stop = TCNT1 + SONAR_TIMEOUT;
    start = TCNT1;

    while (TCNT1 < stop)
    {
        read_sonar(sonar);

        if (sonar->echo) {
            sonar->value = TCNT1 - start;
            sonar->valid = 1;
            sonar->value = sonar_to_centimeters(TIMER_TICK_TO_MILIS(sonar->value));
            break;
        }
    }
}

void task_read_acceleration()
{
    fc_read_acceleration(fc);
}