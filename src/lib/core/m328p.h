#ifndef RAND_M328P_H
#define RAND_M328P_H

// IO header defines for the atmega 328p
// which is on the Arduino Uno

#include <stdint.h>

#define EEPROM_SIZE 2048

#if !MOCK
#define BAUD 9600

#include <util/setbaud.h>

// table to lookup a 328p, use a physical arduino pin to get the 328p pin value
// for instance if you look up dpins[1] you get the CPU's value of the pin 1 on the uno
// but PORTB1 and PORTD1 has the same values so we also need to know what port the pin is on (look at dports)
static uint8_t dpins[] = {_BV(PORTD0), _BV(PORTD1), _BV(PORTD2), _BV(PORTD3),
                          _BV(PORTD4), _BV(PORTD5), _BV(PORTD6), _BV(PORTD7),
                          _BV(PORTB0), _BV(PORTB1), _BV(PORTB2), _BV(PORTB3),
                          _BV(PORTB4), _BV(PORTB5)};
#endif //MOCK


// values of the different atmega 328p registers
// PINx is an input register
// DDRx is a data direction register (tell what pins are input and output)
// PORTx is the output register
typedef enum reg_e {
    PINB_ = 0x03,
    DDRB_ = 0x04,
    PORTB_ = 0x05,

    PINC_ = 0x06,
    DDRC_ = 0x07,
    PORTC_ = 0x08,

    PIND_ = 0x09,
    DDRD_ = 0x0A,
    PORTD_ = 0x0D
} reg_t;

// table to lookup a 328p, use a physical arduino pin to get the 328p port value
// for instance if you look up dports[1] you get the CPU's value of PORTB
// PORTB is the port that contains pin 1 on the arduino
static uint8_t dports[] = {PORTD_, PORTD_, PORTD_, PORTD_, PORTD_, PORTD_, PORTD_,
                           PORTB_, PORTB_, PORTB_, PORTB_, PORTB_, PORTB_, PORTB_};

// physical digital pin values on the arduino uno
typedef enum dpin_e {
    P0,
    P1,
    P2,
    P3,
    P4,
    P5,
    P6,
    P7,
    P8,
    P9,
    P10,
    P11,
    P12,
    P13
} dpin_t;

#define MAXIMUM_PIN P13

// physical analog pin values on the arduino uno
typedef enum apin_e {
    A0,
    A1,
    A2,
    A3,
    A4,
    A5
} apin_t;

// physical rx port (serial receive)
typedef enum rx_e {
    RX0 = 0,
    USB_RX = 0xFF
} rx_t;

// physical rx port (serial send)
typedef enum tx_e {
    TX1 = 1,
    USB_TX = 0xFF
} tx_t;

// physical pwm ports
typedef enum pwm_e {
    PWM3 = 3,
    PWM5 = 5,
    PWM6 = 6,
    PWM9 = 9,
    PWM10 = 10,
    PWM11 = 11
} pwm_t;

typedef enum serial_e {
    SERIAL0 = 0
} serial_t;


#endif //RAND_M328P_H
