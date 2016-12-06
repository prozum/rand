#ifndef RAND_MAP_H
#define RAND_MAP_H

#include "core/io.h"

#define MAX_MAP_SIZE EEPROM_SIZE * 4

#define FIELDS_PER_BYTE 4
#define FULL_FIELD 3 // for bit masking (11 in binary)
#define FIELD_SIZE 2

/**
 * represents the states that a field in the map can be in.
 * Currently a field has 4 states and can be represented by 2 bits.
 */
typedef enum fieldstate_e{
    unvisited = 0,
    visited = 1,
    wall = 2,
    transparent = 3
}fieldstate_t;

void map_init(uint8_t width, uint8_t height, uint8_t clean);

void map_write(uint8_t x, uint8_t y, uint8_t);

uint8_t map_read(uint8_t x, uint8_t y);

void map_clean();

void map_show();

void begin_mapping();

#endif //RAND_MAP_H
