#include "io/io_priv.h"
#include <stdlib.h>
#include <string.h>

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

void digital_write(dpin_t pin, dval_t ps) { }

void uart_init() { }

void uart_putchar(char c) { }

char *write_buffer;
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

