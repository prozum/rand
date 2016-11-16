#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <stdlib.h>
#include <stdint.h>

#include "core/io.h"
#include "kalman/kalman_datafusion.h"

#define SONAR_TIMEOUT 22000 //Just short of 4 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

#if !MOCK
#include <avr/io.h>
#include <util/delay.h>
#endif

typedef struct sonar_s {
    dpin_t trig;
    dpin_t echo;
} sonar_t;

extern char sonar_valid_reading;

sonar_t *sonar_init(dpin_t trig, dpin_t echo);

float read_sonar(sonar_t *sonar);

float sonar_to_meters(float newest_reading);

void pulse_sonar(sonar_t *sonar);

#if MOCK

void pulse_sonar(sonar_t *sonar);

#endif

#endif //RAND_SONAR_H


