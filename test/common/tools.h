#pragma once

#include <stdint.h>

#include <stdlib.h>
#include <stdio.h>
#include <libgen.h>
#include <pthread.h>

#include "sim_avr.h"
#include "avr_ioport.h"
#include "sim_elf.h"
#include "sim_gdb.h"
#include "sim_vcd_file.h"

enum {
    PINB_   = 0x03,
    DDRB_   = 0x04,
    PORTB_  = 0x05,

    PINC_   = 0x06,
    DDRC_   = 0x07,
    PORTC_  = 0x08,

    PIND_   = 0x09,
    DDRD_   = 0x0A,
    PORTD_  = 0x0D
};

enum {
    PIN0,
    PIN1,
    PIN2,
    PIN3,
    PIN4,
    PIN5,
    PIN6,
    PIN7
};


class Tools
{
public:
    static avr_t *avr_init(char *fname, uint32_t freq);
    static void avr_step(avr_t *avr, uint32_t steps);
    static avr_ioport_state_t avr_get_state(avr_t *avr, char port);
    static void avr_set_state(avr_t *avr, char port, int reg, int mask, int v);
};
