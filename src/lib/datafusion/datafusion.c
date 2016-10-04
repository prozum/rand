#include <datafusion.h>

uint16_t get_data_sonar (dpin_t pin, dval_t state)
{
    sensor_data_struct.current_sonar = pulseSonar(pin, state);
}

uint16_t get_data_laser ()
{

}

uint16_t get_data_ir ()
{

}