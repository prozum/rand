#include "task.h"

int main ()
{
    // initialize tasks

    /* insert non-timer dependent tasks here */

    task_init_fc();

    // initialize timer dependent tasks
    task_timer_setup();
    task_arm_fc();

    while (1) {
        task_pulse();

        while (TCNT1 <= MINOR_CYCLE);
    }
}

/*
ISR(TIMER1_OVF_vect)
{
    goto schedule_start;
    return;
}
*/