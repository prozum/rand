#ifndef RAND_MAP_H
#define RAND_MAP_H

#include "core/io.h"

#define MAX_MAP_SIZE EEPROM_SIZE * 4

#define FIELDS_PER_BYTE 4
#define FULL_FIELD 3 // for bit masking (11 in binary)
#define FIELD_SIZE 2

/**
 * Represents the states that a field in the map can be in.
 * Currently a field has 4 states and can be represented by 2 bits.
 */
typedef enum fieldstate_e{
    UNVISITED = 0,
    VISITED = 1,
    WALL = 2,
    WINDOW = 3
}fieldstate_t;

void map_init(uint8_t width, uint8_t height, uint8_t clean);

void map_write(uint8_t x, uint8_t y, fieldstate_t state);

fieldstate_t map_read(uint8_t x, uint8_t y);

void map_clean();

void map_show();


#endif //RAND_MAP_H
