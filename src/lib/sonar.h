#include <avr/io.h>
#include "io.h"

#ifndef RAND_SONAR_H
#define RAND_SONAR_H

// trigger sonar from D0
// sonar echoes are in D7, D8, D12 and D13
uint16_t pulseSonar(dpin_t pin, dval_t state);

#endif //RAND_SONAR_H
