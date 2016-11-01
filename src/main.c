#include "io.h"
#include "sonar.h"

void initialize_sensors();

int main ()
{
    char buffer[65];

    initialize_sensors();

    double sonar_1 = read_sonar();

    snprintf(buffer, 65, "%lf", sonar_1);

    serial_write_string(SERIAL0, buffer);

    // ends the program
    while(1);
}

void initialize_sensors ()
{
    sonar_init();
}

