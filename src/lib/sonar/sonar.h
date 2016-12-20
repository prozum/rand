#ifndef RAND_SONAR_H
#define RAND_SONAR_H

/** @file sonar.h
 * \brief Sonar sensor functions and data
 *
 * \addtogroup SensorSonar
 * @{
 */

#include <stdint.h>
#include <stdlib.h>

#include "core/io.h"
#include "core/log.h"

#define MIN_OUTPUT 110 //!< Roughly 2cm, which is the minimum range for the sonar

#ifndef MOCK
#include <avr/io.h>
#endif

/**
 * The data-structure for storing sonar-readings
 */
typedef struct sonar_s {
    dpin_t trig;    //!< Trigger pin
    dpin_t echo;    //!< Receive pin
    uint8_t valid;  //!< Flag to check if latest value is valid
    uint16_t value; //!< Latest reading in cm
} sonar_t;

/**
 * Initializes a sonar_t struct with the specified trigger- and echo-pin
 * @param sonar - A pointer to the sonar_t struct for the sonar
 * @param trig - The trigger-pin the sonar is wired to
 * @param echo - The echo-pin the sonar is wired to
 */
void sonar_init(sonar_t *sonar, dpin_t trig, dpin_t echo);

/**
 * Checks if the sound-wave had returned to the sonar yet, sets the ->valid field of the struct to 1 if that is the case
 * @param sonar - A pointer to the sonar_t struct for the sonar
 */
void read_sonar(sonar_t *sonar);

/**
 * Pings the sonar with a specified value
 * @param sonar - A pointer to the sonar_t struct for the sonar
 * @param value - The value to write, either HIGH or LOW
 */
void sonar_ping(sonar_t *sonar, dval_t value);

/**
 * Converts the drones reading in milliseconds to centimeters
 * @param millis - The drone's reading in milliseconds
 * @return - The sonar's reading in centimeters
 */
uint16_t sonar_to_centimeters(uint16_t millis);

#if MOCK
/**
 * Pulse the sonar in a LOW-HIGH-LOW pattern
 * @param sonar - The sonar to ping
 */
void pulse_sonar(sonar_t *sonar);

#endif // MOCK

#endif // RAND_SONAR_H

//! @}
