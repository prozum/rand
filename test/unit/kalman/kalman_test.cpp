#include "kalman_test.h"
//add kalman.h
//add log.h

using namespace CppUnit;

static TestSuite *KalmanTest::suite() {
    TestSuite *suite = new TestSuite("KalmanTest");

    //Add tests here:
    suite->addTest(new TestCaller<KalmanTest>(
            "KalmanInit_NullStateValidParams_ExpectInvalidState",
            &KalmanTest::KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog
    ));

    return suite;
}

void KalmanTest::KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog()
{
    kalman_state NullState = NULL;
    double a = 1, r = 10;

    kalman_init (NullState, a, r, SENDER_BOARD);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("The state was initialized against expectation.", NULL, NullState);
}
