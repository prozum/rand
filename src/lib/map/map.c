#include "map.h"
#include "core/log.h"

uint8_t map_width,
        map_height;

void map_init(uint8_t width, uint8_t height, uint8_t clean)
{
    if (map_width * map_height > MAX_MAP_SIZE) {
        SERIOUS_WARNING(SENDER_MAP, "map_init: Map size too big!");
    }

    map_width = width;
    map_height = height;

    if (clean)
        map_clean();
}

void map_write(uint8_t x, uint8_t y, fieldstate_t value)
{
    uint16_t index = y * map_width + x;
    uint16_t addr = index / (uint16_t) FIELDS_PER_BYTE;
    //Use fix16_mod because native avr-% is not boundable
    //fix16_t unscaled_offset = fix16_mod(fix16_from_int(index), FIELDS_PER_BYTE);
    uint16_t offset = (uint16_t) ((index % FIELDS_PER_BYTE) * FIELD_SIZE);
    uint8_t  new_value = 0;

    if(addr >= EEPROM_SIZE) {
        ERROR("Write address value out of bounds!");
        return;
    }
    // Load the byte to be read from
    new_value = eeprom_read(addr);

    new_value &= ~(FULL_FIELD << offset);
    new_value |= value << offset;

    eeprom_write(addr, new_value);
}

fieldstate_t map_read(uint8_t x, uint8_t y)
{
    uint16_t addr = (y * map_width + x) / FIELDS_PER_BYTE;
    uint16_t offset =  ((y * map_width + x) % FIELDS_PER_BYTE) * FIELD_SIZE;

    uint8_t value = eeprom_read(addr);

    return (value >> offset) & FULL_FIELD;
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
                    uart_putchar(CHAR_UNVISITED);
                    break;
                case VISITED:
                    uart_putchar(CHAR_VISITED);
                    break;
                case WALL:
                    uart_putchar(CHAR_WALL);
                    break;
                case WINDOW:
                    uart_putchar(CHAR_TRANSPARENT);
                    break;
                default:
                    ERROR("map_show: Unrecognized character");
            }
        }
        uart_putchar('|');
        uart_putchar('\n');
    }
}
