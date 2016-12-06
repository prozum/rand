#include "core/io.h"

#include <stdlib.h>
#include <string.h>

#define ANALOG_PINS 6
#define ANALOG_BUFFER_SIZE 5
#define DIGITAL_PINS 13
#define DIGITAL_BUFFER_SIZE 5
#define SERIAL_PINS 1
#define SERIAL_BUFFER_SIZE 5

pin_mode_t pin_mode[DIGITAL_PINS];

/***
 * Sets the pin-mode of the specified pin.
 * @param pin to set pin-mode of.
 * @param pm the pin-mode to set the pin to.
 */
void set_pin_mode(dpin_t pin, pin_mode_t pm) {
    pin_mode[pin] = pm;
}

/***
 * Gets the pin-mode of the specified pin (only to control if it has been updated correctly).
 * @param pin pin to get the pin-mode of.
 * @return the pin-mode of specified pin.
 */
pin_mode_t get_pin_mode(dpin_t pin) {
    return pin_mode[pin];
}

//A two dimensional array for storing dvals (i.e. a buffer of some size for each pin)
dval_t digital_buffer[DIGITAL_PINS][DIGITAL_BUFFER_SIZE];
uint8_t dig_buf_cnt[DIGITAL_PINS];

/**
 * Get the latest value written to the specified pin
 * @param pin to read from
 * @return HIGH or LOW depending on what it was set to.
 */
dval_t digital_read(dpin_t pin) {
    dval_t val = digital_buffer[pin][dig_buf_cnt[pin]];

    //Calculate the next buffer position of the given pin
    if (dig_buf_cnt[pin] == 0) {
        dig_buf_cnt[pin] = DIGITAL_BUFFER_SIZE - 1;
    } else {
        dig_buf_cnt[pin]--;
    }

    return val;
}

char uart_val;

char uart_getchar() {
    return uart_val;
}

//A buffer for storing the desired pulses
uint16_t pulse_buffer[DIGITAL_PINS];

/**
 * Set the pulse to return from pulse_in on the specifyied pin
 * @param pin to set pulse for
 * @param pulse
 */
void set_pulse(dpin_t pin, uint16_t pulse) {
    pulse_buffer[pin] = pulse;
}

/**
 * Reads a pulse of state on a given pin
 * @param pin to read from
 * @param state to wait for
 * @param timeout max time in ms to wait
 * @return the length of the pulse
 */
uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout) {
    if (pulse_buffer[pin] > timeout)
        return 0;

    return pulse_buffer[pin];
}

/**
 * Write a specified value to the specified digital pin
 * @param pin to write to
 * @param ps value to write (HIGH or LOW)
 */
void digital_write(dpin_t pin, dval_t ps) {
    //Increments the counter and makes sure it does not exceed buffer size
    dig_buf_cnt[pin] = (dig_buf_cnt[pin] + 1) % DIGITAL_BUFFER_SIZE;
    //Set the value of the digital write buffer to the value specified.
    digital_buffer[pin][dig_buf_cnt[pin]] = ps;
}

/**
 * Get the latest value from a specified pin
 * @param pin the pin to read from
 * @return HIGH or LOW depending on what the pin was set to. Returns -1 is the pin is invalid.
 */
dval_t get_digital_buffer(dpin_t pin) {
    uint8_t prev = (dig_buf_cnt[pin] - 1) % DIGITAL_PINS;

    //Checks that the pin is valid
    if (pin < DIGITAL_PINS && pin >= 0) {
        return digital_buffer[pin][prev];
    }

    return -1;
}

//A two-dimensional array for storing char-pointers (i.e. strings)
uint8_t serial_initialized = 0;
char *serial_buffer[SERIAL_PINS][SERIAL_BUFFER_SIZE];
uint8_t serial_buf_cnt[SERIAL_BUFFER_SIZE];

/**
 * Write a string to the specified pin
 * @param pin to write to
 * @param out the string to write
 */
void serial_write_string(tx_t pin, char *out) {
    //Increment buffer counter for the given pin
    serial_buf_cnt[pin] = (serial_buf_cnt[pin] + 1) % SERIAL_BUFFER_SIZE;
    uint8_t index = serial_buf_cnt[pin];

    //Checks if a string has been allocated on the buffer slot and clears it in that case
    if (serial_buffer[pin][index]) {
        free(serial_buffer[pin][index]);
    }

    //Allocates place for a new string and copies it to the buffer
    serial_buffer[pin][index] = malloc(strlen(out) + 1);
    strcpy(serial_buffer[pin][index], out);
}

void uart_putchar(char c/*, FILE *stream*/)
{
    printf("%c", c);
}

/**
 * Get the latest string written to the specified pin
 * @param pin to get buffer from
 * @return the latest string written to the pin
 */
char *get_write_buffer(tx_t pin) {
    //Init buffer pointers to zero
    if (!serial_initialized) {
        for (int i = 0; i < SERIAL_PINS; i++) {
            for (int j = 0; j < SERIAL_BUFFER_SIZE; j++) {
                serial_buffer[i][j] = 0;
            }
        }
        serial_initialized = 1;
    }
    char *val = serial_buffer[pin][serial_buf_cnt[pin]];

    //Calculate the index of the latest write
    if (serial_buf_cnt[pin] == 0) {
        serial_buf_cnt[pin] = SERIAL_BUFFER_SIZE - 1;
    } else {
        serial_buf_cnt[pin]--;
    }

    return val;
}

/**
 * Clears the buffer for a given pin
 * @param pin
 */
void clear_write_buffer(tx_t pin) {
    int i = 0;
    //Run through the whole buffer
    for (i; i < SERIAL_BUFFER_SIZE; ++i) {
        //Clear deallocate the string if it was allocated.
        if (serial_buffer[pin][i]) {
            free(serial_buffer[pin][i]);
            serial_buffer[pin][i] = 0;
        }
    }
}

/**
 * Read a specified number of bytes from the given pin. This function presents no checks for whether the
 * buffer has been filled or not.
 * @param pin to read from (the buffer is filled by serial_write(rx_t pin))
 * @param len number of bytes to read
 * @return a string from what was filled in the buffer
 */
char *serial_read_string(tx_t pin, uint8_t len) {
    char *serial_string_val = malloc(len + 1);

    //Declare integers for index of 2nd and 3rd dimension of the array
    uint8_t index = 0;
    uint8_t it_index = 0;

    //Emulate a continous buffer by copying from the things that have been written via serial
    int i;
    for (i = 0; i < len; ++i) {
        //If the char at hand is the string terminator (\0) move on to the next string in the buffer.
        if (serial_buffer[pin][index][it_index] == '\0') {
            index = (index + 1) % SERIAL_BUFFER_SIZE;
            it_index = 0;
        }
        //Copy from the calulated string
        serial_string_val[i] = serial_buffer[pin][index][it_index];
        it_index++;
    }

    return serial_string_val;
}

char *serial_read_string_nowait(tx_t pin, uint8_t len) {
    return serial_read_string(pin, len);
}

aval_t analog_buffer[ANALOG_PINS][ANALOG_BUFFER_SIZE];
uint8_t analog_buf_count[ANALOG_PINS];

/***
 * Writes an analog value to the specified pin. The latest value may be read using analog_read.
 * @param pin the pin to write to
 * @param out the value to the pin
 */
void analog_write(apin_t pin, aval_t out) {
    //Increments the counter and makes sure it does not exceed buffer size
    analog_buf_count[pin] = (analog_buf_count[pin] + 1) % ANALOG_BUFFER_SIZE;
    //Set the value of the analog write buffer to the value specified.
    analog_buffer[pin][analog_buf_count[pin]] = out;
}

/***
 * (ØDELAGT!!!, fjernede argument)
 * Read a value from an analog pin. This function will return the latest value written by analog_write
 * to the specified pin.
 * @param pin to write to
 * @return the latest value written by analog_write to the specified pin.
 */
apin_t apin;

uint16_t analog_read() {
    //Get the value from the buffer (when writing it is incremented before filling in the value)
    aval_t val = analog_buffer[apin][analog_buf_count[apin]];

    //Calculate the correct value of the counter (% does not work due to possible overflow)
    if (analog_buf_count[apin] == 0) {
        analog_buf_count[apin] = ANALOG_BUFFER_SIZE - 1;
    } else {
        analog_buf_count[apin]--;
    }

    //Return the found value
    return val;
}

void analog_init() {
    return;
}

void analog_read_setpin(apin_t pin) {
    apin = pin;
}

uint8_t EEP_ARRAY[EEPROM_SIZE];

void eeprom_write(uint16_t p, uint8_t value)
{
    EEP_ARRAY[p] = value;
}

uint8_t eeprom_read(uint16_t p)
{
    return EEP_ARRAY[p];
}


