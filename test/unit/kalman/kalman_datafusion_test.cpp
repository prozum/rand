#include "kalman_datafusion_test.h"

extern "C" {
#include "kalman/kalman_datafusion.h"
#include "sonar/sonar.h"
#include "laser/laser.h"
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

    laser_t *z_0_laser = laser_init(USB_TX);
    sonar_t *z_0_sonar = sonar_init(P2 ,P1);
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - z_0_laser->value);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    laser_t *z_0_laser = laser_init(USB_TX);
    z_0_laser->value = 0.3;
    z_0_laser->valid = 1;
    sonar_t *z_0_sonar = sonar_init(P0, P1);
    z_0_sonar->value = 17671; //about 350cm
    z_0_sonar->valid = 1;
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - sonar_to_meters(z_0_sonar->value));

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    laser_t *z_0_laser = laser_init(USB_TX);
    z_0_laser->value = 3;
    z_0_laser->valid = 1;
    sonar_t *z_0_sonar = sonar_init(P0, P1);
    z_0_sonar->value = 12618; //about 250cm
    z_0_sonar->valid = 1;

    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);
    float diff = abs(state.x_k - z_0_laser->value);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", diff <= r_avg);
}
void KalmanDatafusionTest::KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;
    const float r_avg = 1;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    laser_t *z_0_laser = laser_init(USB_TX);
    z_0_laser->value = 10;
    z_0_laser->valid = 0;
    sonar_t *z_0_sonar = sonar_init(P0, P1);
    z_0_sonar->value = 16661; //330 cm
    z_0_sonar->valid = 0;
    kalman_datafusion_calibrate(&state, z_0_laser, z_0_sonar);

    CPPUNIT_ASSERT_MESSAGE("Filter was not calibrated correctly.", state.x_k == sonar_to_meters(SONAR_TIMEOUT));
}

void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev(){
    kalman_state_matrix state;

    const float a = 1;
    const float b = 0.6;
    const float p_0 = 4;

    kalman_datafusion_init(&state, a, b, p_0, SENDER_BOARD, C, R);

    const float x_prev = 3.7;
    state.x_k = x_prev;
    laser_t *z_laser = laser_init(USB_TX);
    z_laser->value = 1.2;
    z_laser->valid = 1;
    sonar_t *z_sonar = sonar_init(P0, P1);
    z_sonar->value = 6051; //120cm
    z_sonar->valid = 1;
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
    laser_t *z_laser = laser_init(USB_TX);
    z_laser->value = 3;
    sonar_t *z_sonar = sonar_init(P0, P1);
    z_sonar->value = 15145; //300cm
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
