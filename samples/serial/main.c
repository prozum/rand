#include "io.h"
#include <stdlib.h>
#include <string.h>
void main() {
    uart_init();
    //stdout = &uart_output;
    //stdin  = &uart_input;

    serial_write_string(SERIAL0, "***GREETINGS STRANGER***\n\n\n");
    serial_write_string(SERIAL0, "Write something\n\n\n");
    char* thing;
    while(1) {
        thing = serial_read_string(SERIAL0, 10);
        //serial_write_string(SERIAL0, strlen(thing));
        serial_write_string(SERIAL0, thing);
        uart_putchar('\0');
        free(thing);
    }
}

