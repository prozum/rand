#include <avr/io.h>
#include <util/delay.h>
//
///**
// * Calculates the clock-cycles pr millisecond for the target processor
// * @return - The amount of clock-cycles pr millisecond
// */
//#define CLOCK_CYCLES_PER_MS() (F_CPU / 1000000L)
///**
//* Converts from clock-cycles to milliseconds
//* @param x - The clock-cycles to convert
//* @return pm - The time in milliseconds
//*/
//#define CLOCK_CYCLES_TO_MS(x) ((x) / CLOCK_CYCLES_PER_MS())
///**
//* Converts from milliseconds to clock-cycles
//* @param x - The milliseconds to convert
//* @return pm - The number of clock-cycles
//*/
//#define MS_TO_CLOCK_CYCLES(x) ((x)*CLOCK_CYCLES_PER_MS())

#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega328__)
#include "m328p.h"
#elif defined(__AVR_ATmega1280__)
#include "m1280.h"
#endif
