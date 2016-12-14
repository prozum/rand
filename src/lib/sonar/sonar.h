#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <stdlib.h>
#include <stdint.h>

#include "core/io.h"
#include "core/log.h"

#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

#ifndef MOCK
#include <avr/io.h>
#endif

typedef struct sonar_s {
    dpin_t trig;    // trigger pin
    dpin_t echo;    // receive pin
    uint8_t valid;  // flag to check if latest value is valid
    uint16_t value; // latest reading in cm
} sonar_t;

sonar_t *sonar_init(dpin_t trig, dpin_t echo);

void read_sonar(sonar_t *sonar);
void sonar_ping(sonar_t *sonar, dval_t value);

uint16_t sonar_to_centimeters(uint16_t millis);

#if MOCK
void pulse_sonar(sonar_t *sonar);
#endif //MOCK

#endif //RAND_SONAR_H


