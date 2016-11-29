#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <stdlib.h>
#include <stdint.h>

#include "core/io.h"
#include "core/log.h"

#define SONAR_TIMEOUT 11000 //microseconds - Just short of 2 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

#if !MOCK
#include <avr/io.h>
#endif

typedef struct sonar_s {
    dpin_t trig;
    dpin_t echo;
    uint8_t valid; // flag to check if latest value is valid
    float value; // latest reading in cm
} sonar_t;

sonar_t *sonar_init(dpin_t trig, dpin_t echo);

void read_sonar(sonar_t *sonar);
void sonar_ping(sonar_t *sonar, dval_t value);

float sonar_to_meters(float reading);

#if MOCK
void pulse_sonar(sonar_t *sonar);
#endif //MOCK

#endif //RAND_SONAR_H


