#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

class SonarTest : public CppUnit::TestCase {
    CPPUNIT_TEST_SUITE(SonarTest);
        CPPUNIT_TEST(sonarInit_expectTriggerOutAndEchoIn);
        CPPUNIT_TEST(pulseSonar_expectBuffer010);

        CPPUNIT_TEST(readSonar_inRange_expectValidByteOne);
        CPPUNIT_TEST(readSonar_outOfRange_expectValidByteZero);
        CPPUNIT_TEST(readSonar_tooClose_expectValidByteZero);

        CPPUNIT_TEST(sonarToMeters_110_expect2dot41);
        CPPUNIT_TEST(sonarToMeters_8000_expect158dot57);
        CPPUNIT_TEST(sonarToMeters_22000_expect453dot68);
    CPPUNIT_TEST_SUITE_END();
    public :

    void sonarInit_expectTriggerOutAndEchoIn();
    void pulseSonar_expectBuffer010();

    void readSonar_inRange_expectValidByteOne();
    void readSonar_outOfRange_expectValidByteZero();
    void readSonar_tooClose_expectValidByteZero();

    void sonarToMeters_110_expect2dot41();
    void sonarToMeters_8000_expect158dot57();
    void sonarToMeters_22000_expect453dot68();
};
