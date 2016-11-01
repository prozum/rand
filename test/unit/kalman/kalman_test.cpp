#include "kalman_test.h"

void kalman_test::SingleKalmanInit_NullAsStateValidParams_ExpectInvalidState()
{
    kalman_state NullState = NULL;
    double a = 1, r = 10;

    single_kalman_init (NullState, a, r, SENDER_BOARD);

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Stuff", 10, NullState.r);
}
