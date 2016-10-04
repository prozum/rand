#include <stdint.h>
#include "io.h"
#include "sonar.h"

typedef struct sensor_data_s
{
    uint16_t current_sonar;
    uint16_t current_laser;
    uint16_t current_ir;
} sensor_data_t;

sensor_data_t sensor_data_struct;

uint16_t get_data_sonar (dpin_t pin, dval_t state);

uint16_t get_data_laser ();

uint16_t get_data_ir ();