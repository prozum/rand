#include "io.h"

const uint16_t port_to_input[] = {
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) &PINB,
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) &PINC,
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) &PIND,
};