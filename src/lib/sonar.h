#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <avr/io.h>
#include "io.h"
#include "single_kalman.h"

#define SONAR_TRIGGER_PIN 1
#define SONAR_ECHO_PIN 2

void sonar_init();
void pulse_sonar();
double read_sonar();

#endif //RAND_SONAR_H


