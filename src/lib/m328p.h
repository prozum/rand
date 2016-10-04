#ifndef RAND_M328P_H
#define RAND_M328P_H

// IO header defines for the atmega 328p
// which is on the Arduino Uno

#define F_CPU 16000000UL
#define BAUD 9600

static uint8_t pins[] = {_BV(PORTB0), _BV(PORTB1), _BV(PORTB2), _BV(PORTB3),_BV(PORTB4),
                         _BV(PORTB5), _BV(PORTB6), _BV(PORTB7), _BV(PORTD0), _BV(PORTD1),
                         _BV(PORTD2), _BV(PORTD3), _BV(PORTD4), _BV(PORTD5), _BV(PORTD6),
                         _BV(PORTD7)};

typedef enum reg_e {
    PINB_   = 0x03,
    DDRB_   = 0x04,
    PORTB_  = 0x05,

    PINC_   = 0x06,
    DDRC_   = 0x07,
    PORTC_  = 0x08,

    PIND_   = 0x09,
    DDRD_   = 0x0A,
    PORTD_  = 0x0D
} reg_t;

static uint8_t dports[] = {0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03,
                           0x09, 0x09, 0x09, 0x09, 0x09, 0x09, 0x09};

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

typedef enum apin_e {
    A0,
    A1,
    A2,
    A3,
    A4,
    A5
} apin_t;

typedef enum rx_e {
    RX0     = 0
} rx_t;

typedef enum tx_e {
    TX1     = 1
} tx_t;

typedef enum pwm_e {
    PWM3    = 3,
    PWM5    = 5,
    PWM6    = 6,
    PWM10   = 10,
    PWM11   = 11
} pwm_t;

#endif //RAND_M328P_H
