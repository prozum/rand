#include "core/io.h"
#include <stdlib.h>
#include <string.h>

void main() {
    uart_init();
    //stdout = &uart_output;
    //stdin  = &uart_input;

    serial_write_string(SERIAL0, "***GREETINGS STRANGER***");
    uart_putchar('\0');
    serial_write_string(SERIAL0, "Write something");
    uart_putchar('\0');
    char* string;
    while(1) {
        string = serial_read_string(SERIAL0, 10);
        serial_write_string(SERIAL0, string);
        uart_putchar('\0');
        uart_putchar('\n');
        //serial_write_string(SERIAL0, string);
        free(string);
    }
}

