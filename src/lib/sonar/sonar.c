#include "sonar/sonar.h"
#include <util/delay.h>
#include "io/io.h"

#define SONAR_TIMEOUT 22000 //Just short of 4 meters
#define MIN_OUTPUT 110 //Roughly 2cm, which is the minimum range for the sonar
#define MIN_DELAY 65

kalman_state sonar_state;

void sonar_init ()
{
    kalman_init(&sonar_state, 1, 1, SENDER_SONAR); //<-- 1, 1 should be changed when actual values are found.
}

void pulse_sonar() {
    //Setup and pulsing the trigger pin. Might be done in pulse_in tho
    set_pin_mode(SONAR_TRIGGER_PIN, OUTPUT);
    set_pin_mode(SONAR_ECHO_PIN, INPUT);

    //Send a pulse on the trigger pin.
    digital_write(SONAR_TRIGGER_PIN, LOW);
    _delay_ms(2);
    digital_write(SONAR_TRIGGER_PIN, HIGH);
    _delay_ms(2);
    digital_write(SONAR_TRIGGER_PIN, LOW);
}

double read_sonar()
{
    uint16_t duration = pulse_in(SONAR_ECHO_PIN, HIGH, SONAR_TIMEOUT);
    uint8_t extraDelay = 0;

    if (duration >= MIN_OUTPUT && duration <= SONAR_TIMEOUT)
        return single_kalman_run(&sonar_state, duration);
    else if (duration < MIN_DELAY){ //Ensuring a minimum of 65ms between each measurement
        extraDelay = MIN_DELAY - duration;
        _delay_loop_2(extraDelay);
    }

    return sonar_state.x_k;
}