#include <stdint.h>

#include "sonar/sonar.h"



sonar_t *sonar_init(dpin_t trig, dpin_t echo) {
    sonar_t *sonar = malloc(sizeof(sonar_t));

    sonar->trig = trig;
    sonar-> echo = echo;
    sonar->valid = 0;
    sonar->value = 0;

    set_pin_mode(trig, OUTPUT);
    set_pin_mode(echo, INPUT);

    return sonar;
}

void pulse_sonar(sonar_t *sonar) {
    //Send a pulse on the trigger pin.
    digital_write(sonar->trig, LOW);
#if !MOCK
    _delay_ms(2);
#endif
    digital_write(sonar->trig, HIGH);
#if !MOCK
    _delay_ms(2);
#endif
    digital_write(sonar->trig, LOW);
}

float read_sonar(sonar_t *sonar) {
    pulse_sonar(sonar);

    uint16_t duration = pulse_in(sonar->echo, HIGH, SONAR_TIMEOUT);

    if (duration >= MIN_OUTPUT && duration <= SONAR_TIMEOUT) {
        sonar->value = duration;
        sonar->valid = 1;
    } else {
        LOG_WARNING(SENDER_SONAR, "The sonar received faulty value.");
        sonar->valid = 0;
    }

    return sonar->value;
}

float sonar_to_meters(float reading) {
    return 0.01979 * reading + 0.23361;
}