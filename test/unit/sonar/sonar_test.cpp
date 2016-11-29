#include "sonar_test.h"

extern "C" {
#include "core/io.h"
#include "sonar/sonar.h"
}

using namespace std;

CPPUNIT_TEST_SUITE_REGISTRATION(SonarTest);

void SonarTest::pulseSonar_expectBuffer010() {
    sonar_t *sonar;

    sonar = sonar_init(TRIGGER, ECHO);
    pulse_sonar(sonar);

    //The values in the buffer is stored in reverse order:
    dval_t low2 = digital_read((dpin_t) sonar->trig);
    dval_t high = digital_read((dpin_t) sonar->trig);
    dval_t low1 = digital_read((dpin_t) sonar->trig);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The first low pulse was not send correctly", LOW, low1);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The high pulse was not send correctly", HIGH, high);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The second low pulse was not send correctly", LOW, low2);
}

void SonarTest::readSonar_inRange_expectValidByteOne() {
    sonar_t *sonar;

    sonar = sonar_init(TRIGGER, ECHO);

    uint16_t pulse_emulation = 16000;
    set_pulse(sonar->echo, pulse_emulation); // write to pulse buffer

    pulse_sonar(sonar);
    read_sonar(sonar);

    uint8_t ONE = 1;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar did not read a valid value.", 316.92f, sonar->value);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The valid byte was not set correctly", ONE, sonar->valid);
}

void SonarTest::readSonar_outOfRange_expectValidByteZero() {
    sonar_t *sonar;

    sonar = sonar_init(TRIGGER, ECHO);

    uint16_t pulse_emulation = 23000;

    set_pulse(sonar->echo, pulse_emulation);

    pulse_sonar(sonar);
    read_sonar(sonar);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar return the reading, even though it was out of range.",
                                 sonar->value, 0.0f);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar failed to set the valid byte to false.", 0, (int) sonar->value);
}

void SonarTest::readSonar_tooClose_expectValidByteZero() {
    sonar_t *sonar;

    sonar = sonar_init(TRIGGER, ECHO);

    uint16_t pulse_emulation = 50;
    set_pulse(sonar->echo, pulse_emulation);

    pulse_sonar(sonar);
    read_sonar(sonar);

    uint8_t ZERO = 1;
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar return the reading, even though it was out of range.",
                                 sonar->value, 0.0f);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar failed to set the valid byte to false.", ZERO, sonar->valid);
}

void SonarTest::sonarInit_expectTriggerOutAndEchoIn() {
    sonar_t *sonar;

    sonar = sonar_init(TRIGGER, ECHO);

    pin_mode_t mode_echo = get_pin_mode(sonar->echo);
    pin_mode_t mode_trigger = get_pin_mode(sonar->trig);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The echo pin was not setup correctly.", mode_echo, INPUT);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The trigger pin was not setup correctly.", mode_trigger, OUTPUT);
}

void SonarTest::sonarToMeters_110_expect2dot41() {
    float res = sonar_to_meters(110);

    CPPUNIT_ASSERT_EQUAL((float) 2.41, res);
}

void SonarTest::sonarToMeters_8000_expect158dot57() {
    float res = sonar_to_meters(8000);

    CPPUNIT_ASSERT_EQUAL((float) 58.57, res);
}

void SonarTest::sonarToMeters_22000_expect453dot68() {
    float res = sonar_to_meters(22000);

    CPPUNIT_ASSERT_EQUAL((float) 453.68, res);
}

