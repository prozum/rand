#ifndef RAND_IO_H
#define RAND_IO_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <log.h>

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#   include "m328p.h"
#elif defined (__AVR_ATmega1280__)
#   include "m1280.h"
#endif

typedef enum pin_mode_e {
    OUTPUT  = 0,
    INPUT   = 1
} pin_mode_t;

typedef enum pin_state_e {
    LOW     = 0,
    HIGH    = 1
} pin_state_t;

typedef uint16_t analog_data;

// sets the pin mode
void set_pin_mode(dpin_t pin, pin_mode_t pm);

// write state to digital pin
void digital_write(dpin_t pin, pin_state_t ps);

// read state from digital pin
pin_state_t digital_read(dpin_t pin);

void set_analog_mode(apin_t pin, pin_mode_t pm);

void analog_write(apin_t pin, analog_data out);

analog_data analog_read(apin_t pin);

#endif //RAND_IO_H