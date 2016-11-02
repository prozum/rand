#ifndef RAND_M1280_H
#define RAND_M1280_H

// IO header defines for the atmega 1280
// which is on the Arduino Mega

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
    P13,
    P14,
    P15,
    P16,
    P17,
    P18,
    P19,
    P20,
    P21,
    P22,
    P23,
    P24,
    P25,
    P26,
    P27,
    P28,
    P29,
    P30,
    P31,
    P32,
    P33,
    P34,
    P35,
    P36,
    P37,
    P38,
    P39,
    P40,
    P41,
    P42,
    P43,
    P44,
    P45,
    P46,
    P47,
    P48,
    P49,
    P50,
    P51,
    P52,
    P53
} dpin_t;

typedef enum apin_e {
    A0,
    A1,
    A2,
    A3,
    A4,
    A5,
    A6,
    A7,
    A8,
    A9,
    A10,
    A11,
    A12,
    A13,
    A14,
    A15
} apin_t;

typedef enum pwm_e {
    PWM2    = 2;
    PWM3    = 3,
    PWM4    = 4,
    PWM5    = 5,
    PWM6    = 6,
    PWM7    = 7,
    PWM8    = 8,
    PWM9    = 9,
    PWM10   = 10,
    PWM11   = 11,
    PWM12   = 12,
    PWM13   = 13,
    PWM44   = 44,
    PWM45   = 45,
    PWM46   = 46
} pwm_d;

typedef enum rx_e {
    RX0     = 0,
    RX15    = 15,
    RX17    = 17,
    RX19    = 19
} rx_t;

typedef enum tx_e {
    TX1     = 1,
    TX14    = 14,
    TX16    = 16,
    TX18    = 18
} tx_t;

#endif //RAND_M1280_H
