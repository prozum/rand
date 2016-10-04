#include "sonar.h"
#include <util/delay.h>

#define SONAR_TIMEOUT 22000 //Just short of 4 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar
#define MIN_DELAY 65

uint16_t read_sonar(dpin_t echoPin, dpin_t trigPin) {
    //Setup and pulsing the trigger pin. Might be done in pulse_in tho
    set_pin_mode(trigPin, OUTPUT);
    set_pin_mode(echoPin, INPUT);
    digital_write(trigPin, LOW);
    _delay_ms(2);
    digital_write(trigPin, HIGH);
    _delay_ms(2);
    digital_write(trigPin, LOW);

    uint16_t duration = pulse_in(echoPin, HIGH, SONAR_TIMEOUT);
    uint8_t extraDelay = 0;
    if (duration >= MIN_OUTPUT && duration <= SONAR_TIMEOUT)
        return duration;
    else if (duration < MIN_DELAY){ //Ensuring a minimum of 65ms between each measurement
        extraDelay = MIN_DELAY - duration;
        _delay_loop_2(extraDelay);

    }
    return 0;
}