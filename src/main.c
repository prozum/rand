#include "task.h"

void init_not_timed();

int main ()
{
    // initializing timer independent things
    init_not_timed();

    // initialize timer dependent things
    task_timer_setup();
    task_arm_fc();

    while (1) {
        task_pulse();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();
        //Uncomment here to introduce laser in the scheduler
        //task_read_laser_left();
        //task_read_ir();
        //task_read_laser_front();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();
        // Same here
        // task_read_laser_right();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();
        task_read_sonar();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();
        task_navigation();

        while (TCNT1 < MINOR_CYCLE);

        task_navigation();
        TCNT1 = 0;
    }
}