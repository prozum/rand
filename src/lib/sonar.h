#ifndef RAND_SONAR_H
#define RAND_SONAR_H

#include <avr/io.h>
#include "io.h"

// trigger sonar from D0
// sonar echoes are in D7, D8, D12 and D13
uint16_t read_sonar(dpin_t echopin, dpin_t trigpin);

#endif //RAND_SONAR_H
