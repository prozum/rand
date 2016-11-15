#include "map.h"
#define EEPROM_SIZE 2048

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
        /* insert logic that uses the sensors to find a wall*/

        /* insert logic that converts real distance to pixel distance */

        /* insert logic that writes the distance into the eeprom bit per bit */
   // }
}