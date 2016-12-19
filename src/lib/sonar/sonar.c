#include "sonar/sonar.h"
#include "libfixmath/fix16.h"

void sonar_init(sonar_t *sonar, dpin_t trig, dpin_t echo) {
    sonar->trig = trig;
    sonar-> echo = echo;
    sonar->valid = 0;
    sonar->value = 0;

    set_pin_mode(trig, OUTPUT);
    set_pin_mode(echo, INPUT);
}

void sonar_ping(sonar_t *sonar, dval_t value) {
    //Send a pulse on the trigger pin.
    digital_write(sonar->trig, value);
}

void read_sonar(sonar_t *sonar) {
    //sonar->valid = pulse_in(sonar->echo, HIGH, SONAR_TIMEOUT);
    digital_read(sonar->echo);
}

uint16_t sonar_to_centimeters(uint16_t millis) {
    //Speed of sound is 34.32 cm/millisecond and the sound travels twice the distance to the measured object
    const fix16_t speed_of_sound = fix16_from_float(34.32f);
    const fix16_t half = fix16_from_float(0.5f);

    return (uint16_t) fix16_to_int(fix16_mul(fix16_mul(fix16_from_int(millis), speed_of_sound), half));
}

#if MOCK
void pulse_sonar(sonar_t *sonar) {
    sonar_ping(sonar, LOW);
    sonar_ping(sonar, HIGH);
    sonar_ping(sonar, LOW);
}
#endif //MOCK