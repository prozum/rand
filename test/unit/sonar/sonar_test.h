#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

class SonarTest : public CppUnit::TestCase {
    public :
    static CppUnit::Test *suite();

    void sonarInit_expectTriggerOutAndEchoIn();
    void pulseSonar_expectBuffer010();

    void readSonar_inRange_expectValidByteOne();
    void readSonar_outOfRange_expectValidByteZero();
    void readSonar_tooClose_expectValidByteZero();

    void sonarToMeters_110_expect2dot41();
    void sonarToMeters_8000_expect158dot57();
    void sonarToMeters_22000_expect453dot68();
};
