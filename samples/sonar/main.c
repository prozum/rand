#define trigPin 2
#define echoPin 6

#include <sonar.h>

int main(void)
{
    set_pin_mode(13, OUTPUT);
    while(1)
    {
        digital_write(13, HIGH);

        uint16_t duration = read_sonar(echoPin, trigPin);

        _delay_loop_2(duration/100);

        digital_write(13, LOW);


    }
}