#ifndef RAND_MAP_H
#define RAND_MAP_H

/** @file map.h
 * \brief Map reader/writer functions and data
 *
 * \addtogroup Map
 * @{
 */

#include "core/io.h"
#include "libfixmath/fix16.h"

#define MAP_HEIGHT 64 //!< Defines the map's height in fields
#define MAP_WIDTH 64  //!< Defines the map's width in fields

#define CENTIMETERS_PR_FIELD                                                                                           \
    25 //!< Defines the resolution of the map, i.e. one field is CENTIMETERS_PR_FIELD x CENTIMETERS_PR_FIELD

#define MAP_CENTI_HEIGHT MAP_HEIGHT *CENTIMETERS_PR_FIELD //!< Defines the height of the map in centimeters
#define MAP_CENTI_WIDTH MAP_WIDTH *CENTIMETERS_PR_FIELD   //!< Defines the width of the map in centimeters

#define FIELDS_PER_BYTE 4                         //!< Defines how many fields a single byte may store
#define MAX_MAP_SIZE EEPROM_SIZE *FIELDS_PER_BYTE //!< Defines the maximum size of the memory available on the device
#define FULL_FIELD 0b11                           //!< For bit masking (11 in binary)
#define FIELD_SIZE 2                              //!< Defines the size in bits for a single field

#define CHAR_UNVISITED ' ' //!< Defines the character for indicating an UNVISITED field when constructing maps as text
#define CHAR_VISITED '\''  //!< Defines the character for indicating a VISITED field when constructing maps as text
#define CHAR_WALL '#'      //!< Defines the character for indicating a WALL field when constructing maps as text
#define CHAR_TRANSPARENT                                                                                               \
    '&' //!< Defines the character for indicating a TRANSPARENT field when constructing maps as text

/**
 * Represents the states that a field in the map can be in.
 * Currently a field has 4 states and can be represented by 2 bits.
 */
typedef enum fieldstate_e { UNVISITED = 0, VISITED = 1, WALL = 2, WINDOW = 3 } fieldstate_t;

/**
 * Defines a single coordinate on the map, used when scaling from world-position to the map
 */
typedef struct map_coord_s {
    uint8_t x;     //!< The x-coordinate
    uint8_t y;     //!< The y-coordinate
    uint8_t valid; //!< True if the coordinate is within map bounds
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
 * Writes a line to the map
 * @param start - Start coordinate set
 * @param end   - End coordinate set
 * @param state - The value to write (VISITED, UNVISITED, WALL or WINDOW)
 */
void map_write_line(map_coord_t start, map_coord_t end, fieldstate_t state);

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

#endif // RAND_MAP_H

//! @}
