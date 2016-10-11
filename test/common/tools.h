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


class Tools
{
public:
    static avr_t *avr_init(char *fname, uint32_t freq);
    static void avr_step(avr_t *avr, uint32_t steps);
    static avr_ioport_state_t avr_get_state(avr_t *avr, char port);
};
