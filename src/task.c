#include "task.h"

static inline uint16_t TIMER_TICK_TO_MILIS(uint16_t x) { return x / ONE_MS; }

void init_not_timed() {
    // Initialize sensors
    sonar_init(sonar, (dpin_t)SONAR_TRIGGER_PIN, (dpin_t)SONAR_ECHO_PIN);
    laser_init(laser, USB_RX);
    ir_init(top_ir, IR_TOP_PIN);
    ir_init(bottom_ir, IR_BOTTOM_PIN);
    init_fc(fc, TX1, ONE_MS);
    task_init_fc();
    map_init(MAP_WIDTH, MAP_HEIGHT, CLEAN); // Init map and clean it

    nav_state = malloc(sizeof(nav_t));
    world_rep = malloc(sizeof(rep_t));
    init_nav(nav_state);
    init_rep(world_rep, fc, laser, sonar, top_ir, bottom_ir);

    read_sonar(sonar);
    ir_read(bottom_ir);
    ir_read(top_ir);
    // laser_read(laser);
}

void task_timer_setup() {
    // Disable interrupts
    cli();

    // Reset all timer flags
    TCCR1A = 0;
    TCCR1B = 0;

    // Set prescaler of 256
    TCCR1B |= (1 << CS12);
    ICR1 = SCHEDULER_OVERFLOW;

    // Enable interrupts
    sei();
}

void task_init_fc() {
    set_pin_mode(YAW, OUTPUT);
    set_pin_mode(ROLL, OUTPUT);
    set_pin_mode(PITCH, OUTPUT);
    set_pin_mode(THROTTLE, OUTPUT);
}

void task_arm_fc() {
    set_arm(fc);

    int i;

    for (i = 0; i < 20; ++i) {

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE)
            ;

        TCNT1 = 0;
    }
}

void task_disarm_fc() {
    set_disarm(fc);

    int i;

    for (i = 0; i < 20; ++i) {

        task_pulse();

        while (TCNT1 <= MINOR_CYCLE)
            ;

        TCNT1 = 0;
    }
}

void test_dig_and_comp() {
    if (fc->yaw == TWO_MS)
        digital_write(YAW, LOW);

    if (fc->roll == TWO_MS)
        digital_write(ROLL, LOW);

    if (fc->pitch == TWO_MS)
        digital_write(PITCH, LOW);

    if (fc->throttle == TWO_MS)
        digital_write(THROTTLE, LOW);
}

void task_pulse() {
    digital_write(YAW, HIGH);
    digital_write(ROLL, HIGH);
    digital_write(PITCH, HIGH);
    digital_write(THROTTLE, HIGH);

    while (TCNT1 <= ONE_MS)
        ;

    if (fc->yaw == ONE_MS)
        digital_write(YAW, LOW);

    if (fc->roll == ONE_MS)
        digital_write(ROLL, LOW);

    if (fc->pitch == ONE_MS)
        digital_write(PITCH, LOW);

    if (fc->throttle == ONE_MS)
        digital_write(THROTTLE, LOW);

    // This loop MUST be below line 80
    while (TCNT1 <= ONE_AND_A_HALF_MS)
        ;

    if (fc->yaw == ONE_AND_A_HALF_MS)
        digital_write(YAW, LOW);

    if (fc->roll == ONE_AND_A_HALF_MS)
        digital_write(ROLL, LOW);

    if (fc->pitch == ONE_AND_A_HALF_MS)
        digital_write(PITCH, LOW);

    if (fc->throttle == ONE_AND_A_HALF_MS)
        digital_write(THROTTLE, LOW);

    while (TCNT1 <= TWO_MS)
        ;

    if (fc->yaw == TWO_MS)
        digital_write(YAW, LOW);

    if (fc->roll == TWO_MS)
        digital_write(ROLL, LOW);

    if (fc->pitch == TWO_MS)
        digital_write(PITCH, LOW);

    if (fc->throttle == TWO_MS)
        digital_write(THROTTLE, LOW);
}

void task_navigation() { navigation(world_rep, nav_state); }

void task_read_ir() {
    ir_read(bottom_ir);
    ir_read(top_ir);
}

void task_read_sonar() {
    sonar->valid = 0;

    uint16_t start, stop;
    uint16_t next_ping = TCNT1 + TWO_MS;

    // Ping and LOW-HIGH-LOW with 2 milis delay in-between
    sonar_ping(sonar, LOW);
    while (TCNT1 < next_ping)
        ;

    next_ping = TCNT1 + TWO_MS;
    sonar_ping(sonar, HIGH);

    while (TCNT1 < next_ping)
        ;
    sonar_ping(sonar, LOW);

    // Start timer and read sonar and stop timer
    stop = TCNT1 + SONAR_TIMEOUT;
    start = TCNT1;

    while (TCNT1 < stop) {
        read_sonar(sonar);

        if (sonar->echo) {
            sonar->value = TCNT1 - start;
            sonar->valid = 1;
            sonar->value = sonar_to_centimeters(TIMER_TICK_TO_MILIS(sonar->value));
            break;
        }
    }
}

void conversion() { sonar_to_centimeters(TIMER_TICK_TO_MILIS(sonar->value)); }

void task_read_acceleration() { fc_read_acceleration(fc); }