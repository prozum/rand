#ifndef RAND_M1280_H
#define RAND_M1280_H

// IO header defines for the atmega 1280
// which is on the Arduino Mega

#define EEPROM_SIZE 4096

typedef enum reg_e {
    PORTB_,
    PORTC_,
    PORTD_,
    PORTE_,
    PORTG_,
    PORTH_,
    PORTJ_,
    PORTL_,
} reg_t;

// table to lookup a 1280, use a physical arduino pin to get the 328p pin value
// for instance if you look up dpins[1] you get the CPU's value of the pin 1 on the uno
// but PORTB1 and PORTD1 has the same values so we also need to know what port the pin is on (look at dports)
const uint8_t dpinss = {
    _BV(PORTE0), _BV(PORTE1), _BV(PORTE4), _BV(PORTE5), // E
    _BV(PORTG5),                                        // G
    _BV(PORTE3),                                        // E
    _BV(PORTH3), _BV(PORTH4), _BV(PORTH5), _BV(PORTH6), // H
    _BV(PORTB4), _BV(PORTB5), _BV(PORTB6), _BV(PORTB7), // B
    _BV(PORTJ1), _BV(PORTJ0),                           // J
    _BV(PORTH1), _BV(PORTH0),                           // H
    _BV(PORTD3), _BV(PORTD2), _BV(PORTD1), _BV(PORTD0), // D
    _BV(PORTA0), _BV(PORTA1), _BV(PORTA2), _BV(PORTA3), _BV(PORTA4), _BV(PORTA5), _BV(PORTA6), _BV(PORTA7), // A
    _BV(PORTC7), _BV(PORTC6), _BV(PORTC5), _BV(PORTC4), _BV(PORTC3), _BV(PORTC2), _BV(PORTC1), _BV(PORTC0), // C
    _BV(PORTD7),                                        // D
    _BV(PORTG2), _BV(PORTG1), _BV(PORTG0),              // G
    _BV(PORTL7), _BV(PORTL6), _BV(PORTL5), _BV(PORTL4), _BV(PORTL3), _BV(PORTL2), _BV(PORTL1), _BV(PORTL0), // L
    _BV(PORTB3), _BV(PORTB2), _BV(PORTB1), _BV(PORTB0)  // B
};


// table to lookup a 1280, use a physical arduino pin to get the 1280½ port value
// for instance if you look up dports[1] you get the CPU's value of PORTB
// PORTB is the port that contains pin 1 on the arduino
static uint8_t dports[] = {
    PORTE_, PORTE_, PORTE_, PORTE_,                                 // D0-3
    PORTG_,                                                         // D4
    PORTE_,                                                         // D5
    PORTH_, PORTH_, PORTH_, PORTH_,                                 // D6-9
    PORTB_, PORTB_, PORTB_, PORTB_,                                 // D10-13
    PORTJ_, PORTJ_,                                                 // D14-15
    PORTH_, PORTH_,                                                 // D16-17
    PORTD_, PORTD_, PORTD_, PORTD_,                                 // D18-21
    PORTA_, PORTA_, PORTA_, PORTA_, PORTA_, PORTA_, PORTA_, PORTA_, // D22-29
    PORTC_, PORTC_, PORTC_, PORTC_, PORTC_, PORTC_, PORTC_, PORTC_, // D30-37
    PORTD_,                                                         // D38
    PORTG_, PORTG_, PORTG_,                                         // D41
    PORTL_, PORTL_, PORTL_, PORTL_, PORTL_, PORTL_, PORTL_, PORTL_, // D42-49
    PORTB_, PORTB_, PORTB_, PORTB_,                                 // D50-53
};


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
    PWM2 = 2,
    PWM3 = 3,
    PWM4 = 4,
    PWM5 = 5,
    PWM6 = 6,
    PWM7 = 7,
    PWM8 = 8,
    PWM9 = 9,
    PWM10 = 10,
    PWM11 = 11,
    PWM12 = 12,
    PWM13 = 13,
    PWM44 = 44,
    PWM45 = 45,
    PWM46 = 46
} pwm_d;

typedef enum rx_e {
    RX0 = 0,
    RX15 = 15,
    RX17 = 17,
    RX19 = 19
} rx_t;

typedef enum tx_e {
    TX1 = 1,
    TX14 = 14,
    TX16 = 16,
    TX18 = 18
} tx_t;

typedef enum serial_e {
    SERIAL0 = 0
} serial_t;

#endif //RAND_M1280_H
