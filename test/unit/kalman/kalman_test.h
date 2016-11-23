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
#include <cmath>

class KalmanTest : public CppUnit::TestCase {
        CPPUNIT_TEST_SUITE(KalmanTest);
        CPPUNIT_TEST(KalmanInit_NullAsStateValidParams_ExpectValidStateMalloced);
        CPPUNIT_TEST(KalmanInit_ValidStateValidParams_ExpectStateWithEqualParams);
        CPPUNIT_TEST(KalmanRun_NullStateValidParam_ExpectStateStillNull);
        CPPUNIT_TEST(KalmanRun_ValidStatezkGxk_ExpectxkGxkprev);
        CPPUNIT_TEST(KalmanRun_ValidStatezkLxk_ExpectxkLxkprev);
        CPPUNIT_TEST(KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0);
        CPPUNIT_TEST_SUITE_END();

public:

    void KalmanInit_NullAsStateValidParams_ExpectValidStateMalloced();

    void KalmanInit_ValidStateValidParams_ExpectStateWithEqualParams();

    void KalmanRun_NullStateValidParam_ExpectStateStillNull();

    void KalmanRun_ValidStatezkGxk_ExpectxkGxkprev();

    void KalmanRun_ValidStatezkLxk_ExpectxkLxkprev();

    void KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0();
};
