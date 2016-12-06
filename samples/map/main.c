#include "core/io.h"
#include "map/map.h"

#define WIDTH 64
#define HEIGHT 64

void draw_block(uint8_t x, uint8_t y, uint8_t offset, uint8_t size)
{
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map_write(x + offset + i, y + offset + j, 1);
        }
    }
}

int main ()
{
    int x, y;

    uart_init();

    map_init(WIDTH, HEIGHT, 1);

    draw_block(4, 1, 38, 3);
    draw_block(9, 5, 38, 3);
    draw_block(1, 9, 38, 3);
    draw_block(5, 9, 38, 3);
    draw_block(9, 9, 38, 3);

    while (1) {
        serial_write_string(SERIAL0, "+-----------------------------------------|EEPROM|-----------------------------------------+\n");
        map_show();
        serial_write_string(SERIAL0, "+------------------------------------------------------------------------------------------+\n\n");
    }
}