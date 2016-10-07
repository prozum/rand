#include "io.h"
void main() {
    uart_init();
    //stdout = &uart_output;
    //stdin  = &uart_input;

    serial_write_string(SERIAL0, "***GREETINGS STRANGER***\n\n\n");
    char input[10];
    int i = 0;
    /**
     * Dette stykke virker ikke.
     */
    while(1) {
        while(1) {
            input[i] = uart_getchar();
            if(input[i]='\n')
                break;
            i++;
        }

        serial_write_string(SERIAL0, input);
    }

}

