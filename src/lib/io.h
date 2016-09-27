#ifndef RAND_IO_H
#define RAND_IO_H

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <log.h>


#define F_CPU 16000000UL
#define BAUD 9600

typedef enum pin_mode_e {
    OUTPUT  = 0,
    INPUT   = 1
} pin_mode_t;

typedef enum pin_state_e {
    LOW     = 0,
    HIGH    = 1
} pin_state_t;

typedef enum port_e {
    _PORTB = 0,
    _PORTC = 1,
    _PORTD = 2
} port_t ;

typedef struct pin_s {
    uint8_t digital[16];
    
} pin_t;

pin_t pins = {
        {_BV(PORTB0), _BV(PORTB1), _BV(PORTB2), _BV(PORTB3), _BV(PORTB4), _BV(PORTB5), _BV(PORTB6), _BV(PORTB7),
                _BV(PORTD0), _BV(PORTD1), _BV(PORTD2), _BV(PORTD3), _BV(PORTD4), _BV(PORTD5), _BV(PORTD6), _BV(PORTD7)},
};

// DDRx is data direction register
// PORTx is the port state

// analog IO example:
//      http://www.avrfreaks.net/forum/tut-c-newbies-guide-avr-adc?name=PNphpBB2&file=viewtopic&t=56429

// sets the pin mode
void io_set_pin(port_t port, uint8_t pin, pin_mode_t pm);

// write state to digital pin
void io_digital_write(port_t port, uint8_t pin, pin_state_t ps);

// read state from digital pin
pin_state_t io_digital_read(port_t port, uint8_t pin);

void io_analog_write(uint8_t pin, uint16_t);
uint16_t io_analog_read(uint8_t pin);

#endif //RAND_IO_H