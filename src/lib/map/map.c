#include "map.h"
#include "core/log.h"

uint8_t map_width,
        map_height;

void map_init(uint8_t width, uint8_t height, uint8_t clean)
{
    if (map_width * map_height > MAX_MAP_SIZE) {
        SERIOUS_WARNING(SENDER_MAP, "Map size too big!");
    }

    map_width = width;
    map_height = height;

    if (clean)
        map_clean();
}

void map_write(uint8_t x, uint8_t y, uint8_t value)
{
    uint16_t addr = (y * map_width + x) / FIELDS_PER_BYTE;
    uint16_t offset =  ((y * map_width + x) % FIELDS_PER_BYTE) * FIELD_SIZE;

    uint8_t new_value = eeprom_read(addr); //load the byte to be read from

    uint8_t mask = FULL_FIELD << offset * FIELD_SIZE; //safety mask
    new_value = (new_value & ~(mask)) | ((value << offset) & mask);

    eeprom_write(addr, new_value);
}

uint8_t map_read(uint8_t x, uint8_t y)
{
    uint16_t addr = (y * map_width + x) / FIELDS_PER_BYTE;
    uint16_t offset =  ((y * map_width + x) % FIELDS_PER_BYTE) * FIELD_SIZE;;

    uint8_t value = eeprom_read(addr);

    return (value >> (offset)) & FULL_FIELD;
}

void map_clean()
{
    uint16_t map_size = (map_width * map_height) / FIELDS_PER_BYTE;
    if (map_width * map_height % FIELDS_PER_BYTE)
        map_size++;
    for (int i = 0; i < map_size; i++) {
        eeprom_write(i, 0);
    }
}

void map_show()
{
    uint8_t x, y;
    for (y = 0; y < map_height; y++) {
        uart_putchar('|');
        for (x = 0; x < map_width; x++) {
            switch (map_read(x, y)) {
                case UNVISITED:
                    uart_putchar(' ');
                    break;
                case VISITED:
                    uart_putchar('\'');
                    break;
                case WALL:
                    uart_putchar('#');
                    break;
                case TRANSPARENT:
                    uart_putchar('&');
                    break;
                default:
                    ERROR("Unrecognized character");
            }
        }
        uart_putchar('|');
        uart_putchar('\n');
    }
}

void begin_mapping()
{
    eeprom_write(0, 1);
    uint8_t value = eeprom_read(0);

#if MOCK
#include <stdio.h>
    printf("blabla %d\n", value);
#endif

  //  for (int i = 0; i < EEPROM_SIZE; i++)
   // {
        /* insert logic that uses the sensors to find a WALL*/

        /* insert logic that converts real distance to pixel distance */

        /* insert logic that writes the distance into the eeprom bit per bit */
   // }
}