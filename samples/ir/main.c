#include <avr/interrupt.h>
#include <avr/io.h>

#include "core/io.h"
#include "ir/ir.h"

int main(void) {
    adc_init();
    uart_init();
    analog_read_setpin(A0);
    ir_t *ir = IR_init(A0);

    while (1) {
        char string[5];
        serial_write_string(SERIAL0, "height: ");
        uint8_t data = analog_read(A0);
        sprintf(string, "%d\n", IR_read(ir));
        serial_write_string(SERIAL0, string);
    }
}
