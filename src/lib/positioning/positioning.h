//
// Created by Lee on 08/11/2016.
//

#ifndef RAND_POSITIONING_H
#define RAND_POSITIONING_H

#include <stdint.h>
#include "kalman.h"

void positioning_init ();
float calculate_a (kalman_state *state);
void check_avoidance ();
void update_u_k ();

#endif //RAND_POSITIONING_H


