#include "kalman_datafusion_test.h"
#include "../../../../../../usr/lib/avr/include/stdlib.h"

extern "C" {
#include "kalman/kalman_datafusion.h"
#include "sonar/sonar.h"
}

CPPUNIT_TEST_SUITE_REGISTRATION(KalmanDatafusionTest);

void KalmanDatafusionTest::KalmanDFInit_NullStateValidParams_StateMallocedAndInitialized(){
    kalman_state_matrix *state = NULL;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(state, a, b, p_0, SENDER_BOARD, C, R);

    CPPUNIT_ASSERT_MESSAGE("The state was not initialized", state != NULL);
    CPPUNIT_ASSERT_MESSAGE("a-value not set in state", state->a != a);
    CPPUNIT_ASSERT_MESSAGE("b-value not set in state", state->b != b);
    CPPUNIT_ASSERT_MESSAGE("p_0-value not set in state", state->p_k != p_0);
    for (int i = 0; i < 2; ++i) {
        CPPUNIT_ASSERT_MESSAGE("A C-value was not set correctly", state->C[i][0] != C[i][0]);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            CPPUNIT_ASSERT_MESSAGE("A R-value was not set correctly", state->R[i][j] != R[i][j]);
        }
    }
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateValidParams_StateInitialized(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    CPPUNIT_ASSERT_MESSAGE("a-value not set in state", state.a != a);
    CPPUNIT_ASSERT_MESSAGE("b-value not set in state", state.b != b);
    CPPUNIT_ASSERT_MESSAGE("p_0-value not set in state", state.p_k != p_0);
    for (int i = 0; i < 2; ++i) {
        CPPUNIT_ASSERT_MESSAGE("A C-value was not set correctly", state.C[i][0] != C[i][0]);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            CPPUNIT_ASSERT_MESSAGE("A R-value was not set correctly", state.R[i][j] != R[i][j]);
        }
    }
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateCNull_StateInitializedWithCzero(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, NULL, R);

    CPPUNIT_ASSERT_MESSAGE("a-value not set in state", state.a != a);
    CPPUNIT_ASSERT_MESSAGE("b-value not set in state", state.b != b);
    CPPUNIT_ASSERT_MESSAGE("p_0-value not set in state", state.p_k != p_0);
    for (int i = 0; i < 2; ++i) {
        CPPUNIT_ASSERT_MESSAGE("A C-value was not set correctly", state.C[i][0] != 0);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            CPPUNIT_ASSERT_MESSAGE("A R-value was not set correctly", state.R[i][j] != R[i][j]);
        }
    }
}
void KalmanDatafusionTest::KalmanDFInit_ValidStateRNull_StateInitializedWithRone(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, NULL);

    CPPUNIT_ASSERT_MESSAGE("a-value not set in state", state.a != a);
    CPPUNIT_ASSERT_MESSAGE("b-value not set in state", state.b != b);
    CPPUNIT_ASSERT_MESSAGE("p_0-value not set in state", state.p_k != p_0);
    for (int i = 0; i < 2; ++i) {
        CPPUNIT_ASSERT_MESSAGE("A C-value was not set correctly", state.C[i][0] != C[i][0]);
    }
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            CPPUNIT_ASSERT_MESSAGE("A R-value was not set correctly", state.R[i][j] != 0);
        }
    }
}

void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0EQSonar0_xkCloseToBoth(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float z_0_laser = 3;
    const float z_0_sonar = 3;
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - z_0_laser);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float z_0_laser = 0.3;
    const float z_0_sonar = 3.5;
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - z_0_sonar);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float z_0_laser = 3;
    const float z_0_sonar = 2.5;
    sonar_valid_reading = 0;

    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - z_0_laser);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float z_0_laser = 10;
    //laser_valid_reading = 0;
    const float z_0_sonar = 3.3;
    sonar_valid_reading = 0;
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);

    //22000 is SONAR_TIMEOUT (maximum possible reading)
    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", state.x_k == sonar_to_meters(22000));
}

void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float x_prev = 3.7;
    state.x_k = x_prev;
    const float z_laser = 1.2;
    const float z_sonar = 1.2;
    kalman_datafusion_filter(&state, z_laser, z_sonar);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", x_prev < state.x_k);

}
void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxGTxprev_xkHigherThanxprev(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float x_prev = 1.2;
    state.x_k = x_prev;
    const float z_laser = 3;
    const float z_sonar = 3;
    kalman_datafusion_filter(&state, z_laser, z_sonar);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", state.x_k > x_prev);
}

void KalmanDatafusionTest::setUp() {
    R = (float**) malloc(DATAFUSION_UNITS * sizeof(float*));
    for (int k = 0; k < DATAFUSION_UNITS; ++k) {
        R[k] = (float*) malloc(DATAFUSION_UNITS * sizeof(float));
    }
    R[0][0] = 1;
    R[0][1] = 0;
    R[1][0] = 0;
    R[1][1] = 1;

    C = (float**) malloc(sizeof(float*));
    C[0] = (float*) malloc(DATAFUSION_UNITS * sizeof(float*));
    C[0][0] = 1;
    C[0][1] = 1;
}

void KalmanDatafusionTest::tearDown() {
    for (int i = 0; i < DATAFUSION_UNITS; ++i) {
        free(R[i]);
    }
    free(R);

    free(C[0]);
    free(C);
}
