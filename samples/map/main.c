#include "core/io.h"
#include "map/map.h"

#define WIDTH 64
#define HEIGHT 64

void draw_block(uint8_t x, uint8_t y, uint8_t offset, uint8_t size) {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            map_write(x + offset + i, y + offset + j, VISITED);
        }
    }
}

int main() {
    int x, y;

    uart_init();

    map_init(WIDTH, HEIGHT, 1);

    map_write(10, 10, VISITED);
    printf("val: %d\n", map_read(10, 10));

    serial_write_string(
        TX1, "+-----------------------------------------|EEPROM|-----------------------------------------+\n");
    map_show();
    serial_write_string(
        TX1, "+------------------------------------------------------------------------------------------+\n\n");

    return 0;
}