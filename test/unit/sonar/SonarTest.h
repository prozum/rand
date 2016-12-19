#pragma once

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

#define TRIGGER P2
#define ECHO P3

class SonarTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(SonarTest);
    CPPUNIT_TEST(sonarInit_expectTriggerOutAndEchoIn);
    CPPUNIT_TEST(pulseSonar_expectBuffer010);

    /*CPPUNIT_TEST(readSonar_inRange_expectValidByteOne);
    CPPUNIT_TEST(readSonar_outOfRange_expectValidByteZero);
    CPPUNIT_TEST(readSonar_tooClose_expectValidByteZero);*/

    CPPUNIT_TEST(sonarToCentimeters_11millis_expect188);
    CPPUNIT_TEST(sonarToCentimeters_1millis_expect17);
    CPPUNIT_TEST(sonarToCentimeters_5millis_expect85);
    CPPUNIT_TEST_SUITE_END();

  public:
    void sonarInit_expectTriggerOutAndEchoIn();

    void pulseSonar_expectBuffer010();

    /*void readSonar_inRange_expectValidByteOne();
    void readSonar_outOfRange_expectValidByteZero();
    void readSonar_tooClose_expectValidByteZero();*/

    void sonarToCentimeters_11millis_expect188();

    void sonarToCentimeters_1millis_expect17();

    void sonarToCentimeters_5millis_expect85();
};
