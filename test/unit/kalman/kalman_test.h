#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

#include <stdlib.h>
#include <cmath>

class KalmanTest : public CppUnit::TestCase {
        CPPUNIT_TEST_SUITE(KalmanTest);
        CPPUNIT_TEST(KalmanInit_ValidParams_ExpectValidStateMalloced);
        CPPUNIT_TEST(KalmanRun_NullStateValidParam_ExpectStateStillNull);
        CPPUNIT_TEST(KalmanRun_ValidStatezkGxk_ExpectxkGxkprev);
        CPPUNIT_TEST(KalmanRun_ValidStatezkLxk_ExpectxkLxkprev);
        CPPUNIT_TEST(KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0);
        CPPUNIT_TEST_SUITE_END();

public:

    void KalmanInit_ValidParams_ExpectValidStateMalloced();

    void KalmanRun_NullStateValidParam_ExpectStateStillNull();

    void KalmanRun_ValidStatezkGxk_ExpectxkGxkprev();

    void KalmanRun_ValidStatezkLxk_ExpectxkLxkprev();

    void KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0();
};
