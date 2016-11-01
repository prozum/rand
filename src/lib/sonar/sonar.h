#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <avr/io.h>
#include "io/io.h"
#include "kalman/kalman_datafusion.h"

#define SONAR_TRIGGER_PIN 1
#define SONAR_ECHO_PIN 2

extern char sonar_valid_reading;

void sonar_init();
float read_sonar();
float sonar_to_meters();

#endif //RAND_SONAR_H


