#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <stdlib.h>
#include <stdint.h>

#include "core/io.h"
#include "core/log.h"

#define SONAR_TIMEOUT 22000 //Just short of 4 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

#if !MOCK
#include <avr/io.h>
#include <util/delay.h>
#endif

typedef struct sonar_s {
    dpin_t trig;
    dpin_t echo;
    uint8_t valid; // flag to check if latest value is valid
    uint16_t value; // latest reading in mikroseconds
} sonar_t;

sonar_t *sonar_init(dpin_t trig, dpin_t echo);

void read_sonar(sonar_t *sonar);

float sonar_to_meters(float reading);

void pulse_sonar(sonar_t *sonar);

#endif //RAND_SONAR_H


