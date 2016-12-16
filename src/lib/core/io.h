#ifndef RAND_IO_H
#define RAND_IO_H

/** @file io.h
 * \brief Input/Output functions and data
 *
 * \addtogroup IO
 * @{
 */

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
#define MAX_IO_STR_LEN 100

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

/**
 * Sets the pin-mode of a specified pin to either INPUT or OUTPUT
 * @param pin - The pin to set the pin-mode of
 * @param pm - The pin-mode
 */
void set_pin_mode(dpin_t pin, pin_mode_t pm);

/**
 * Write a value to a specified digital pin
 * @param pin - The pin to write to
 * @param ps - The value to write (may be either HIGH or LOW)
 */
void digital_write(dpin_t pin, dval_t ps);
/**
 * Read a value from a specified digital pin
 * @param pin - The pin to read from
 * @return - The value that was read (may be either HIGH or LOW)
 */
dval_t digital_read(dpin_t pin);

/**
 * Sets the pin for the following analog_read()s
 * @param pin The pin to read from
 */
void analog_read_setpin(apin_t pin);

/**
 * Read a value from the analog pin specified in the last call to analog_read_setpin
 * @return The value read from the pin
 */
aval_t analog_read();

/**
 * Reads a digital pulse on the specified pin
 * @param pin - The pin to read from
 * @param state - The digital value to start and end the pulse with
 * @param timeout - The maximum time to read for
 * @return - The length of the pulse in ms
 */
uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout);

/** Writes a given string over serial connection
 * @param pin - the serial pin to write to (Currently not used)
 * @param out - the string to be written. (MUST END WITH '\0')
 */
void serial_write_string(tx_t pin, char *out);

/** reads the next n amount of characters from the a serial connection and returns them as a string
 * @param pin - the serial pin to read from (Currently not used)
 * @param len - The amount of characters to read
 * @return - the string representation of the read characters
 */
char *serial_read_string(tx_t pin, uint8_t len);

/** reads the next n characters from the a serial connection and returns them as a string
 * only reads if there is unread data in the uart.
 * @param pin - the serial pin to read from (Currently not used)
 * @param len - The amount of characters to read
 * @return - the string representation of the read characters or NULL if an empty string if no data is available
 */
char *serial_read_string_nowait(tx_t pin, uint8_t len);

/** initializes the avr uart for serial communication.
 */
void uart_init();

/** Writes a character to the avr processor's uart.
 * \param c - The character to be written
 */
void uart_putchar(char c);

/** Returns the next character read from the avr processor's uart.
 * @return - The character read
 */
char uart_getchar(/*FILE *stream*/);

/** Returns the next character read from the avr processor's uart only if there is unread data available.
 * @return The character read or '\0' if no unread data is available
 */
char uart_trygetchar(/*FILE *stream*/);

/** Sets the pulse width emitting from a pin
 * @param pin The pin to write to
 * @param width the width of the pwm pulse
 */
//void pwn_write(pwm_t pin, uint16_t width);

/**
 * Initializes the analog-to-digital converter
 */
void adc_init();

/**
 * Writes a byte to the eeprom at the specified address
 * @param p - The address to write to
 * @param value - The byte to write to the eeprom
 */
void eeprom_write(uint16_t p, uint8_t value);
/**
 * Reads a byte from the eeprom at the specified address
 * @param p - The address to read from
 * @return
 */
uint8_t eeprom_read(uint16_t p);
/**
 * Shows the content of the whole eeprom
 */
void eeprom_show();

#if MOCK
/**
 * Get the latest string written to the specified pin
 * @param pin - the pin to get the latest string from
 * @return - the latest string written to the pin
 */
char *get_write_buffer(tx_t pin);
/**
 * Get a string from the index of the serial buffer for the pin
 * @param pin - The pin to get the serial buffer for
 * @param index - The index in the buffer to read from
 * @return - The string found on said index of the buffer
 */
char *get_write_buffer_index(tx_t pin, uint8_t index);
/**
 * Clears the whole buffer of a specified pin
 * @param pin - The pin to clear
 */
void clear_write_buffer(tx_t pin);

/**
 * Get the latest digital value written to the specified pin
 * @param pin - The pin to get the latest value from
 * @return - The latest value
 */
dval_t get_digital_buffer(dpin_t pin);

/**
 * Sets the pulse to be read from pulse_in on the specified pin
 * @param pin - The pin to set the pulse for
 * @param pulse - The length of the pulse in milliseconds
 */
void set_pulse(dpin_t pin, uint16_t pulse);

/**
 * Gets the pin-mode of a specified pin
 * @param pin - The pin-mode to lookup pin-mode for
 * @return - The pin-mode
 */
pin_mode_t get_pin_mode(dpin_t pin);

#endif //MOCK

#endif //RAND_IO_H

//! @}
