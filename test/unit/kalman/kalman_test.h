#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

class KalmanTest : public CppUnit::TestCase
{
    CPPUNIT_TEST_SUITE(KalmanTest);
        CPPUNIT_TEST(KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog);
    CPPUNIT_TEST_SUITE_END();

public:

    void KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog ();
};
