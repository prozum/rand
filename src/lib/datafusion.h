#include <stdint.h>
#include "io.h"
#include "sonar.h"

typedef struct raw_sensor_data_s
{
    uint16_t current_sonar;
    uint16_t current_laser;
    uint16_t current_ir;
} raw_sensor_data_t;

typedef struct fused_sensor_data_s
{

} fused_sensor_data_t;

static raw_sensor_data_t raw_sensor_data;

void datafusion_feed (raw_sensor_data_t raw);

raw_sensor_data_t get_fused_data (fused_sensor_data_t);