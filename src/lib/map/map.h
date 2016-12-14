#ifndef RAND_MAP_H
#define RAND_MAP_H

#include "core/io.h"
#include "libfixmath/fix16.h"

#define MAP_HEIGHT 64
#define MAP_WIDTH 64

#define CENTIMETERS_PR_PIXEL 50

#define MAP_CENTI_HEIGHT MAP_HEIGHT * CENTIMETERS_PR_PIXEL
#define MAP_CENTI_WIDTH MAP_WIDTH * CENTIMETERS_PR_PIXEL

#define FIELDS_PER_BYTE 4
#define MAX_MAP_SIZE EEPROM_SIZE * FIELDS_PER_BYTE
#define FULL_FIELD 0b11 // for bit masking (11 in binary)
#define FIELD_SIZE 2

#define CHAR_UNVISITED ' '
#define CHAR_VISITED '\''
#define CHAR_WALL '#'
#define CHAR_TRANSPARENT '&'

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

typedef struct map_coord_s {
    uint8_t x, y;
} map_coord_t;
/**
 * Initialzes a map on the EEPROM of the Arduino with specified width and height
 * @param width - The width of the map
 * @param height - The height of the map
 * @param clean - Flag that indicated whether the EEPROM should be cleaned
 */
void map_init(uint8_t width, uint8_t height, uint8_t clean);
/**
 * Writes a value to the map at specified position
 * @param x - x-coordinate to write to
 * @param y - y-coordinate to write to
 * @param state - The value to write (VISITED, UNVISITED, WALL or WINDOW)
 */
void map_write(uint8_t x, uint8_t y, fieldstate_t state);

/**
 * Reads a value from the map at specified position
 * @param x - x-coordinate
 * @param y - y-coordinate
 * @return - The state of the given position (VISITED, UNVISITED, WALL or WINDOW)
 */
fieldstate_t map_read(uint8_t x, uint8_t y);

/**
 * Cleans the map
 */
void map_clean();
/**
 * Shows the map
 */
void map_show();


#endif //RAND_MAP_H
