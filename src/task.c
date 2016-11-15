#include "task.h"

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
    init_fc(ONE_MS);

    set_pin_mode(YAW, OUTPUT);
    set_pin_mode(ROLL, OUTPUT);
    set_pin_mode(PITCH, OUTPUT);
    set_pin_mode(THROTTLE, OUTPUT);
}

void task_arm_fc()
{
    set_arm();

    int i;

    for (i = 0; i < 20; ++i) {

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);

        TCNT1 = 0;
    }
}

void task_disarm_fc()
{
    set_disarm();

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

    if(YAW == ONE_MS)
        digital_write(YAW, LOW);

    if(ROLL == ONE_MS)
        digital_write(ROLL, LOW);

    if(PITCH == ONE_MS)
        digital_write(PITCH, LOW);

    if(THROTTLE == ONE_MS)
        digital_write(THROTTLE, LOW);

    while (TCNT1 <= ONE_AND_A_HALF_MS);

    if(YAW == ONE_AND_A_HALF_MS)
        digital_write(YAW, LOW);

    if(ROLL == ONE_AND_A_HALF_MS)
        digital_write(ROLL, LOW);

    if(PITCH == ONE_AND_A_HALF_MS)
        digital_write(PITCH, LOW);

    if(THROTTLE == ONE_AND_A_HALF_MS)
        digital_write(THROTTLE, LOW);

    while (TCNT1 <= TWO_MS);

    if(YAW == TWO_MS)
        digital_write(YAW, LOW);

    if(ROLL == TWO_MS)
        digital_write(ROLL, LOW);

    if(PITCH == TWO_MS)
        digital_write(PITCH, LOW);

    if(THROTTLE == TWO_MS)
        digital_write(THROTTLE, LOW);
}