#include "io/io.h"

#include <stdlib.h>
#include <string.h>

#define DIGITAL_PINS 13
#define DIGITAL_BUFFER_SIZE 5
#define SERIAL_PINS 1
#define SERIAL_BUFFER_SIZE 5

void set_pin_mode(dpin_t pin, pin_mode_t pm) { }

dval_t digital_read_val;

dval_t digital_read(dpin_t pin)
{
    return digital_read_val;
}

char uart_val;

char uart_getchar() {
    return uart_val;
}

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout) { }

//13 is the number of digital pins on the board and 5 is the buffer size
dval_t digital_buffer[DIGITAL_PINS][DIGITAL_BUFFER_SIZE];
uint8_t dig_buf_cnt [DIGITAL_PINS];
void digital_write(dpin_t pin, dval_t ps) {
    //Increments the counter and makes sure it does not exceed buffer size
    dig_buf_cnt[pin] = (dig_buf_cnt[pin] + 1) % DIGITAL_BUFFER_SIZE;
    //Set the value of the digital write buffer to the value specified.
    digital_buffer[pin][dig_buf_cnt[pin]] = ps;
}

dval_t get_digital_buffer(dpin_t pin, uint8_t index) {
    if (pin < DIGITAL_PINS && pin >= 0) {
        if(index < DIGITAL_BUFFER_SIZE && index > DIGITAL_BUFFER_SIZE) {
            return digital_buffer[pin][index];
        }
    }

    return -1;
}

void uart_init() { }

void uart_putchar(char c) { }

char **write_buffer;
void serial_write_string(tx_t pin, char *out) {
    if(write_buffer) {
        free(write_buffer);
    }
    write_buffer = malloc(strlen(out) * sizeof(char));
    strcpy(write_buffer, out);
}
char *get_write_buffer() {
    return write_buffer;
}
void clear_write_buffer() {
    if(write_buffer) {
        free(write_buffer);
    }
}

char *serial_string_val;

char* serial_read_string(tx_t pin, int len ) {
    return serial_string_val;
}

