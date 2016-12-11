#ifndef RAND_IO_H
#define RAND_IO_H

#include <stdint.h>
#include <stdio.h>

#ifndef MOCK
extern const uint16_t port_to_input[];

#include <avr/io.h>
#include <util/delay.h>
#include "core/log.h"

#define CLOCK_CYCLES_PER_MS() ( F_CPU / 1000000L )
#define CLOCK_CYCLES_TO_MS(x) ( (x) / CLOCK_CYCLES_PER_MS() )
#define MS_TO_CLOCK_CYCLES(x) ( (x) * CLOCK_CYCLES_PER_MS() )
#endif //MOCK

#if defined (__AVR_ATmega328P__) || defined (__AVR_ATmega328__)
#include "m328p.h"
#elif defined (__AVR_ATmega1280__)
#include "m1280.h"
#endif

#define MS_PR_SEC 1000

typedef enum pin_mode_e {
    INPUT = 0,
    OUTPUT = 1
} pin_mode_t;

typedef enum dval_e {
    LOW = 0,
    HIGH = 1
} dval_t;

typedef uint16_t aval_t;

typedef uint8_t sval_t;

// sets the pin mode
void set_pin_mode(dpin_t pin, pin_mode_t pm);

/// Initializes a pin to write pwm signals
/// \param pin the pin to be initialized.
//void pwm_init(pwm_t pin);

// write state to digital pin
void digital_write(dpin_t pin, dval_t ps);

// read state from digital pin
dval_t digital_read(dpin_t pin);

//void set_analog_mode(apin_t pin, pin_mode_t pm);
void analog_read_setpin(apin_t pin);

//void analog_write(apin_t pin, aval_t out);

aval_t analog_read();

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout);

/// Writes a given string over serial connection
/// \param pin the serial pin to read from **Currently not used**
/// \param out the string to be written. **Should end with '\0'**
void serial_write_string(tx_t pin, char *out);

/// reads the next n amount of characters from the a serial connection and returns them as a string
/// \param pin the serial pin to read from **Currently not used**
/// \param len The amount of characters to read
/// \return the string representation of the read characters
char *serial_read_string(tx_t pin, uint8_t len);

/// reads the next n amount of characters from the a serial connection and returns them as a string
/// only reads if there is unread data in the uart.
/// \param pin the serial pin to read from **Currently not used**
/// \param len The amount of characters to read
/// \return the string representation of the read characters or NULL if an empty string if no data is available
char *serial_read_string_nowait(tx_t pin, uint8_t len);

/// initializes the avr uart for serial communication.
void uart_init();

/// Writes a character to the avr processor's uart.
/// \param c The character to be written
void uart_putchar(char c/*, FILE *stream*/);

/// Returns the next character read from the avr processor's uart.
/// \return The character read.
char uart_getchar(/*FILE *stream*/);

/// Returns the next character read from the avr processor's uart only if there is unread data available.
/// \return The character read or '\0' if no unread data is available
char uart_trygetchar(/*FILE *stream*/);

/// Sets the pulse width emitting from a pin
/// \param pin The pin to write to
/// \param width the width of the pwm pulse
//void pwn_write(pwm_t pin, uint16_t width);

void adc_init();


void eeprom_write(uint16_t p, uint8_t value);

uint8_t eeprom_read(uint16_t p);

void eeprom_show();

#if MOCK

char *get_write_buffer(tx_t pin);

char *get_write_buffer_index(tx_t pin, uint8_t index);

void clear_write_buffer(tx_t pin);

dval_t get_digital_buffer(dpin_t pin);

void set_pulse(dpin_t pin, uint16_t pulse);

pin_mode_t get_pin_mode(dpin_t pin);

#endif //MOCK

#endif //RAND_IO_H
