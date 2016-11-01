#include <single_kalman.h>
#include "ir.h"
#include "io.h"
#include <math.h>

//The IR is placed on an 8-bit pin
#define IR_MAX_INPUT 255

kalman_state IR_top_state;
kalman_state IR_bottom_state;

void IR_init() {
    kalman_init(&IR_top_state, 1, 1, SENDER_IR); //<-- 1, 1 should be changed!
    kalman_init(&IR_bottom_state, 1, 1, SENDER_IR); //<-- 1, 1 should be changed!
}

float read_top_IR() {

}

float read_bottom_IR() {

}

float IR_top_to_meters() {
    return 7881.82 * pow(IR_top_state.x_k, -1.086);
}

float IR_bottom_to_meters() {
    return 7881.82 * pow(IR_bottom_state.x_k, -1.086);
}