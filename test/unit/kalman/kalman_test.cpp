#include "kalman_test.h"

extern "C" {
#include "kalman/kalman.h"
}

CPPUNIT_TEST_SUITE_REGISTRATION(KalmanTest);

void KalmanTest::KalmanInit_ValidParams_ExpectValidStateMalloced() {
    kalman_state *NullState = NULL;

    fix16_t a = fix16_from_int(1), r = fix16_from_int(10);

    NullState = kalman_init(a, r, SENDER_BOARD);

    CPPUNIT_ASSERT_MESSAGE("The state was initialized against expectation.", NullState != NULL);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The r value was not set correctly.", r, NullState->r);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The a value was not set correctly.", a, NullState->a);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The u_k value was not set to 0.", fix16_from_float(0.0f), NullState->u_k);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The g_k value was not set to 0.", fix16_from_float(0.0f), NullState->g_k);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The p_k value must be > than 0.", fix16_from_float(10.0f), NullState->p_k);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The x_k value was not set to 0.", fix16_from_float(0.0f), NullState->x_k);
}

void KalmanTest::KalmanRun_NullStateValidParam_ExpectStateStillNull() {
    kalman_state *state = NULL;

    kalman_run(state, fix16_from_int(10));

    CPPUNIT_ASSERT_MESSAGE("The kalman_state was initialized against expectation", state == NULL);
}

void KalmanTest::KalmanRun_ValidStatezkGxk_ExpectxkGxkprev() {
    kalman_state *state;
    float a = fix16_from_int(1), r = fix16_from_int(1), z_k = fix16_from_int(10), x_prev = fix16_from_int(4);
    state = kalman_init(a, r, SENDER_BOARD);
    state->x_k = x_prev;

    kalman_run(state, z_k);

    std::string msg = "x_k: " + std::to_string(state->x_k) + ", g_k: " + std::to_string(x_prev);
    CPPUNIT_ASSERT_MESSAGE(msg, state->x_k > x_prev);
}

void KalmanTest::KalmanRun_ValidStatezkLxk_ExpectxkLxkprev() {
    kalman_state *state;
    fix16_t a = fix16_from_int(1), r = fix16_from_int(1), z_k = fix16_from_int(400), x_prev = fix16_from_int(200);
    state = kalman_init(a, r, SENDER_BOARD);
    state->x_k = x_prev;

    kalman_run(state, z_k);

    std::string msg = "x_k was supposed to increase. x_k = " + std::to_string(fix16_to_float(state->x_k)) +
            ", x_prev = " + std::to_string(fix16_to_float(x_prev));
    CPPUNIT_ASSERT_MESSAGE(msg, state->x_k > x_prev);
}

void KalmanTest::KalmanCalibrate_ValidStateValidz0_ExpectxkCloseToz0() {
    kalman_state *state;
    fix16_t a = fix16_from_int(1), r = fix16_from_int(1), z_0 = fix16_from_int(60);
    fix16_t x_k = fix16_from_int(10);
    state = kalman_init(a, r, SENDER_BOARD);
    state->x_k = x_k;
    kalman_calibrate(state, z_0);

    float absDiff = std::abs(state->x_k - state->z_k);

    std::string msg = "x_k should be close to z_0, x_k = " + std::to_string(fix16_to_float(state->x_k)) + ", z_0 = "
                      + std::to_string(fix16_to_float(z_0)) + ", r = " + std::to_string(fix16_to_float(state->r));
    CPPUNIT_ASSERT_MESSAGE(msg, absDiff < r);
}
