#include <sonar.h>

#define TRIG_PIN 2
#define ECHO_PIN 6


int main(void)
{
    set_pin_mode(13, OUTPUT);
    while(1)
    {
        digital_write(13, HIGH);

        uint16_t duration = read_sonar(ECHO_PIN, TRIG_PIN);

        //_delay_loop_2(duration/100);

        digital_write(13, LOW);


    }
}