#ifndef RAND_IO_H
#define RAND_IO_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

typedef enum pin_mode_e {
    OUTPUT  = 0,
    INPUT   = 1
} pin_mode_t;

// DDRx is data direction register
// PORTx is the port state

// analog IO example:
//      http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-adc?name=PNphpBB2&file=viewtopic&t=56429

// set a pin to either input or output
void io_set_pin(uint8_t port, uint8_t pin, pin_mode_t pmode);
void io_clear_pin(uint8_t port, uint8_t pin);

void io_digital_write(uint8_t pin, char out);
char io_digital_read(uint8_t pin);

void io_analog_write(uint8_t pin, uint16_t);
uint16_t io_analog_read(uint8_t pin);

#endif //RAND_IO_H