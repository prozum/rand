#include "core/io.h"
#include "map/map.h"

int main ()
{
    int i;
    char buffer[64];

    uart_init();

    while (1) {
        for (i = 0; i < EEPROM_SIZE; i++) {
            eeprom_write(i, i % 2);
        }
        for (i = 0; i < EEPROM_SIZE; i++) {
            uint8_t value = eeprom_read(i);
            sprintf(buffer, "i: %u value: %u \n", i, value);
            serial_write_string(SERIAL0, buffer);
        }
    }
}