#ifndef RAND_POSITIONING_H
#define RAND_POSITIONING_H

#define MAX_NEGATIVE_ACCELERATION 0
#define NO_ACCELERATION 1
#define MAX_POSITIVE_ACCELERATION 2
//This defines that we belive that there is a window, if the laser reads more than a 0.5m longer than the sonar.
#define WINDOW_RECON_THRESHOLD 0.5
#define MIN_SAFE_DIST 0.4

#include <stdint.h>
#include "kalman/kalman.h"

void positioning_init();

float calculate_a(kalman_state *state);

void check_avoidance();

void update_u_k();

#endif //RAND_POSITIONING_H


