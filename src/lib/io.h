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

typedef enum dval_e {
    LOW     = 0,
    HIGH    = 1
} dval_t;

typedef uint16_t aval_t;

typedef uint8_t sval_t;

// sets the pin mode
void set_pin_mode(dpin_t pin, pin_mode_t pm);

// write state to digital pin
void digital_write(dpin_t pin, dval_t ps);

// read state from digital pin
dval_t digital_read(dpin_t pin);

void set_analog_mode(apin_t pin, pin_mode_t pm);

void analog_write(apin_t pin, aval_t out);

aval_t analog_read(apin_t pin);

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout);

// Write to serial pin
void serial_write_byte(tx_t pin, sval_t out);

void serial_write_string(tx_t pin, sval_t *out);

sval_t serial_read(rx_t pin);

#endif //RAND_IO_H
