#include "kalman_test.h"
extern "C" {
#include "kalman/kalman.h"
}

CPPUNIT_TEST_SUITE_REGISTRATION(KalmanTest);

void KalmanTest::KalmanInit_NullAsStateValidParams_ExpectInvalidStateSentToLog()
{
    kalman_state *NullState = NULL;

    double a = 1, r = 10;

    kalman_init(NullState, a, r, SENDER_BOARD);

    CPPUNIT_ASSERT_MESSAGE("The state was initialized against expectation.", NullState != NULL);
    CPPUNIT_ASSERT_MESSAGE("The r value was not set correctly.", NullState->r == r);
    CPPUNIT_ASSERT_MESSAGE("The a value was not set correctly.", NullState->a == a);
    CPPUNIT_ASSERT_MESSAGE("The u_k value was not set to 0.", NullState->u_k == 0);
    CPPUNIT_ASSERT_MESSAGE("The g_k value was not set to 0.", NullState->g_k == 0);
    CPPUNIT_ASSERT_MESSAGE("The p_k value must be > than 0.", NullState->p_k > 0);
    CPPUNIT_ASSERT_MESSAGE("The x_k value was not set to 0.", NullState->x_k == 0);
}

void KalmanTest::KalmanInit_ValidStateValidParams_ExpectStateWithEqualParams(){
    kalman_state pState;

    double a = 1, r = 10;

    kalman_init(&pState, a, r, SENDER_BOARD);

    CPPUNIT_ASSERT_MESSAGE("The r value was not set correctly.", pState.r == r);
    CPPUNIT_ASSERT_MESSAGE("The a value was not set correctly.", pState.a == a);
    CPPUNIT_ASSERT_MESSAGE("The u_k value was not set to 0.", pState.u_k == 0);
    CPPUNIT_ASSERT_MESSAGE("The g_k value was not set to 0.", pState.g_k == 0);
    CPPUNIT_ASSERT_MESSAGE("The p_k value must be > than 0.", pState.p_k > 0);
    CPPUNIT_ASSERT_MESSAGE("The x_k value was not set to 0.", pState.x_k == 0);
}

void KalmanTest::KalmanRun_NullStateValidParam_ExpectStateStillNull(){
    kalman_state *state = NULL;

    kalman_run(state, 10);

    CPPUNIT_ASSERT_MESSAGE("The kalman_state was initialized against expectation", state == NULL);
}

void KalmanTest::KalmanRun_ValidStatezkGxk_ExpectxkGxkprev(){
    kalman_state state;
    float a = 1, r = 1, z_k = 10, x_prev = 4;
    kalman_init(&state, a, r, SENDER_BOARD);
    state.x_k = x_prev;

    kalman_run(&state, z_k);

    CPPUNIT_ASSERT_MESSAGE("The x_k value was supposed to increase.", state.x_k > x_prev);
}

void KalmanTest::KalmanRun_ValidStatezkLxk_ExpectxkLxkprev(){
    kalman_state state;
    float a = 1, r = 1, z_k = 4, x_prev = 10;
    kalman_init(&state, a, r, SENDER_BOARD);
    state.x_k = x_prev;

    kalman_run(&state, z_k);

    CPPUNIT_ASSERT_MESSAGE("The x_k value was supposed to increase.", state.x_k < x_prev);
}

void KalmanTest::KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0(){
    kalman_state state;
    float a = 1, r = 1, z_0 = 6;
    kalman_init(&state, a, r, SENDER_BOARD);
    kalman_calibrate(&state, z_0);

    float absDiff = std::abs(state.x_k - state.z_k);

    CPPUNIT_ASSERT_MESSAGE("x_k should be close to z_0.", absDiff < r);
}
