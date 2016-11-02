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
public:
    static CppUnit::TestSuite *suite();

    void KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog ();
};
