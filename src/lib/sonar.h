#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <avr/io.h>
#include "io.h"
#include "single_kalman.h"

#define SONAR_TRIGGER_PIN 1
#define SONAR_ECHO_PIN 2

char sonar_valid_reading = 0;

void sonar_init();
float read_sonar();
float sonar_to_meters();

#endif //RAND_SONAR_H


