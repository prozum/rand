#include <stdint.h>

#include "sonar/sonar.h"

float newest_reading;
char sonar_valid_reading = 0;

sonar_t *sonar_init(dpin_t trig, dpin_t echo) {
    sonar_t *sonar = malloc(sizeof(sonar_t));

    sonar->trig = trig;
    sonar-> echo = echo;

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
        newest_reading = duration;
        sonar_valid_reading = 1;
    } else {
        LOG_WARNING(SENDER_SONAR, "The sonar received faulty value.");
        sonar_valid_reading = 0;
    }

    return newest_reading;
}

float sonar_to_meters(float newest_reading) {
    return 0.01979 * newest_reading + 0.23361;
}