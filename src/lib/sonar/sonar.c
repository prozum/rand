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

void sonar_ping(sonar_t *sonar, dval_t value) {
    //Send a pulse on the trigger pin.
    digital_write(sonar->trig, value);
}

void read_sonar(sonar_t *sonar) {
    //sonar->valid = pulse_in(sonar->echo, HIGH, SONAR_TIMEOUT);
    digital_read(sonar->echo);
}

uint16_t sonar_to_centimeters(float millis) {
    //Speed of sound is 34.32 cm/millisecond and the sound travels twice the distance to the measured object
    return (uint16_t) (millis * 34.32f) / 2.0f;
}

void set_sonar(sonar_t *sonar, float value){
    sonar->value = value;
}

#if MOCK
void pulse_sonar(sonar_t *sonar) {
    sonar_ping(sonar, LOW);
    sonar_ping(sonar, HIGH);
    sonar_ping(sonar, LOW);
}
#endif //MOCK