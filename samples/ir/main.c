#include <avr/io.h>
#include <avr/interrupt.h>

#include "core/io.h"


int main(void) {
    adc_init();
    analog_read_setpin(A0);

    while (1) {
        char string[5];
        sprintf(string, "%d\n", analog_read());
        serial_write_string(SERIAL0, string);
    }
}
