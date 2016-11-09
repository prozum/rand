#include "KalmanDatafusion_test.h"
extern "C" {
#include "kalman/kalman_datafusion.h"
}

CPPUNIT_TEST_SUITE_REGISTRATION(KalmanDatafusionTest);

void KalmanDatafusionTest::KalmanDFInit_NullStateValidParams_StateMallocedAndInitialized(){

}
void KalmanDatafusionTest::KalmanDFInit_ValidStateValidParams_StateInitialized(){

}
void KalmanDatafusionTest::KalmanDFInit_ValidStateCNull_StateInitializedWithCzero(){

}
void KalmanDatafusionTest::KalmanDFInit_ValidStateRNull_StateInitializedWithRone(){

}

void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0EQSonar0_xkCloseToBoth(){

}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaser0MuchHigherThanSonar0_xkCloseToSonar(){

}
void KalmanDatafusionTest::KalmanDFCalibrate_ValidStateLaserValidSonarInvalid_xkCloseToLaser(){

}
void KalmanDatafusionTest::KalmanDFCalibrate_BothOutOfRange_xkEQSonarMax(){

}

void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxLTxprev_xkLowerThanxprev(){

}
void KalmanDatafusionTest::KalmanDFFilter_SonarxEQLaserxGTxprev_xkHigherThanxprev(){

}
