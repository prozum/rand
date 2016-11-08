#include "sonar/sonar.h"
#include "core/io.h"


#define SONAR_TIMEOUT 22000 //Just short of 4 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar

float newest_reading;
char sonar_valid_reading = 0;

void sonar_init ()
{
    //Setup pins of the sonar.
    set_pin_mode(SONAR_TRIGGER_PIN, OUTPUT);
    set_pin_mode(SONAR_ECHO_PIN, INPUT);
}

void pulse_sonar() {
    //Send a pulse on the trigger pin.
    digital_write(SONAR_TRIGGER_PIN, LOW);
#if !MOCK
    _delay_ms(2);
#endif
    digital_write(SONAR_TRIGGER_PIN, HIGH);
#if !MOCK
    _delay_ms(2);
#endif
    digital_write(SONAR_TRIGGER_PIN, LOW);
}

float read_sonar()
{
    pulse_sonar();

    uint16_t duration = pulse_in(SONAR_ECHO_PIN, HIGH, SONAR_TIMEOUT);

    if (duration >= MIN_OUTPUT && duration <= SONAR_TIMEOUT) {
        newest_reading = duration;
        sonar_valid_reading = 1;
    }
    else {
        LOG_WARNING(SENDER_SONAR, "The sonar received faulty value.");
        sonar_valid_reading = 0;
    }

    return newest_reading;
}

float sonar_to_meters(float newest_reading) {
    return 0.01979 * newest_reading + 0.23361;
}