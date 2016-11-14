#include "task.h"

void task_timer_setup() {
    // disable interrupts
    cli();

    // reset all timer flags
    TCCR1A = 0;
    TCCR1B = 0;

    // set prescaler of 256
    TCCR1B |= (1 << CS12);

    // enable interrupts
    sei();
}

void task_arm_fc() {

}

void task_start_pulse() {

}

void task_stop_pulse() {

}

int main() {

}
