#include "sonar_test.h"
#include "sonar/sonar.h"
#include "io/io.h"

using namespace std;
using namespace CppUnit;

static Test *SonarTest::suite() {
    //Instantiate test suite
    TestSuite *suiteOfTests = new TestSuite("SonarTest");

    //Add all test methods.
    suiteOfTests->addTest((new TestCaller<SonarTest>(
            "sonarInit_expectTriggerOutAndEchoIn", &SonarTest::sonarInit_expectTriggerOutAndEchoIn));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "pulseSonar_expectBuffer010", &SonarTest::pulseSonar_expectBuffer010));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "readSonar_inRange_expectValidByteOne", &SonarTest::readSonar_inRange_expectValidByteOne));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "readSonar_outOfRange_expectValidByteZero", &SonarTest::readSonar_outOfRange_expectValidByteZero));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "readSonar_tooClose_expectValidByteZero", &SonarTest::readSonar_tooClose_expectValidByteZero));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "sonarToMeters_110_expect2.41", &SonarTest::sonarToMeters_110_expect2dot41
    ));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "sonarToMeters_8000_expect158.57", &SonarTest::sonarToMeters_8000_expect158dot57
    ));

    suiteOfTests->addTest(new TestCaller<SonarTest>(
            "sonarToMeters_22000_expect453.68", &SonarTest::sonarToMeters_22000_expect453dot68
    ));

    //And return the suite
    return suiteOfTests;
}

void SonarTest::pulseSonar_expectBuffer010() {
    sonar_init();
    pulse_sonar();

    //The values in the buffer is stored in reverse order:
    dval_t low2 = digital_read(SONAR_TRIGGER_PIN);
    dval_t high = digital_read(SONAR_TRIGGER_PIN);
    dval_t low1 = digital_read(SONAR_TRIGGER_PIN);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The first low pulse was not send correctly", LOW, low1);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The high pulse was not send correctly", HIGH, high);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The second low pulse was not send correctly", LOW, low2);
}

void SonarTest::readSonar_inRange_expectValidByteOne() {
    sonar_int();
    uint16_t pulse_emulation = 16000;
    set_pulse(SONAR_ECHO_PIN, pulse_emulation);

    uint16_t reading = read_sonar();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar did not read a valid value.", pulse_emulation, reading);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The valid byte was not set correctly", 1, sonar_valid_reading);
}

void SonarTest::readSonar_outOfRange_expectValidByteZero() {
    sonar_init();
    uint16_t pulse_emulation = 23000;
    set_pulse(SONAR_ECHO_PIN, pulse_emulation);

    uint16_t reading = read_sonar();

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE("The sonar return the reading, eventhough it was out of range.",
                                    pulse_emulation == reading);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar failed to set the valid byte to false.", 0, sonar_valid_reading);
}

void SonarTest::readSonar_tooClose_expectValidByteZero() {
    sonar_init();
    uint16_t pulse_emulation = 50;
    set_pulse(SONAR_ECHO_PIN, pulse_emulation);

    uint16_t reading = read_sonar();

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE("The sonar return the reading, eventhough it was out of range.",
                                          pulse_emulation == reading);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The sonar failed to set the valid byte to false.", 0, sonar_valid_reading);
}

void SonarTest::sonarInit_expectTriggerOutAndEchoIn() {
    sonar_init();

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The echo pin was not setup correctly.", SONAR_ECHO_PIN, INPUT);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The trigger pin was not setup correctly.", SONAR_TRIGGER_PIN, OUTPUT);
}

void SonarTest::sonarToMeters_110_expect2dot41() {
    float res = sonar_to_meters(110);

    CPPUNIT_ASSERT_EQUAL(2.41, res);
}

void SonarTest::sonarToMeters_8000_expect158dot57() {
    float res = sonar_to_meters(8000);

    CPPUNIT_ASSERT_EQUAL(158.57, res);
}

void SonarTest::sonarToMeters_22000_expect453dot68() {
    float res = sonar_to_meters(22000);

    CPPUNIT_ASSERT_EQUAL(453.68, res);
}

