#include "io/io.h"

//#if !MOCK
#define NOT_A_PORT 0

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

//#endif