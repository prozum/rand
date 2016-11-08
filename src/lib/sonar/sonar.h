#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#if !MOCK
#include <avr/io.h>
#include <util/delay.h>
#endif
#include "core/io.h"
#include "kalman/kalman_datafusion.h"

#define SONAR_TRIGGER_PIN 1
#define SONAR_ECHO_PIN 2

extern char sonar_valid_reading;

void sonar_init();
float read_sonar();
float sonar_to_meters(float newest_reading);
#if MOCK
void pulse_sonar();
#endif

#endif //RAND_SONAR_H


