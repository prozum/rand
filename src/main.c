#include "task.h"
#include "sonar/sonar.h"
#include "laser/laser.h"
#include "ir/ir.h"
#include "positioning/positioning.h"

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

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;

        task_pulse();

        while (TCNT1 < MINOR_CYCLE);

        TCNT1 = 0;
    }
}