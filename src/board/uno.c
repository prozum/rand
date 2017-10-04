#include "uno.h"

#include <avr/io.h>

uint8_t dpins[] = {_BV(PORTD0), _BV(PORTD1), _BV(PORTD2), _BV(PORTD3), _BV(PORTD4), _BV(PORTD5), _BV(PORTD6),
                   _BV(PORTD7), _BV(PORTB0), _BV(PORTB1), _BV(PORTB2), _BV(PORTB3), _BV(PORTB4), _BV(PORTB5)};

uint8_t dports[] = {PORTD_, PORTD_, PORTD_, PORTD_, PORTD_, PORTD_, PORTD_,
                    PORTD_, PORTB_, PORTB_, PORTB_, PORTB_, PORTB_, PORTB_};
