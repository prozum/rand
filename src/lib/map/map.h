#ifndef RAND_MAP_H
#define RAND_MAP_H

#include "core/io.h"

#define MAX_MAP_SIZE EEPROM_SIZE * 8

void map_init(uint8_t width, uint8_t height, uint8_t clean);

void map_write(uint8_t x, uint8_t y, uint8_t);

uint8_t map_read(uint8_t x, uint8_t y);

void map_clean();

void map_show();

void begin_mapping();

#endif //RAND_MAP_H
