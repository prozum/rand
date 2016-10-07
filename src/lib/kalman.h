#include <stdint.h>
#include "io.h"

typedef static struct {
    double q; //process noise covariance
    double r; //measurement noise covariance
    double x; //value
    double p; //estimation error covariance
    double k; //kalman gain
} kalman_state;

kalman_state kalman_init (double q, double r, double p, double intial_value);

void kalman_update(kalman_state* state, double measurement);

