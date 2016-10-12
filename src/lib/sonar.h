#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <avr/io.h>
#include "io.h"
#include "single_kalman.h"

// trigger sonar from D0
// sonar echoes are in D7, D8, D12 and D13

void sonar_init (dpin_t echoPin, dpin_t trigPin);
double read_sonar(dpin_t echopin, dpin_t trigpin);

#endif //RAND_SONAR_H


