#include "ir/ir.h"

kalman_state IR_top_state;
kalman_state IR_bottom_state;

uint8_t IR_to_cm[256] =
        {
                19, 19, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18, 17,
                17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 16, 16,
                16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 15, 15,
                15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15,
                14, 14, 14, 14, 80, 79, 78, 76, 75, 74, 73, 72, 71, 70, 69, 68,
                67, 66, 65, 64, 64, 63, 62, 61, 60, 60, 59, 58, 58, 57, 56, 56,
                55, 54, 54, 53, 53, 52, 51, 51, 50, 50, 49, 49, 48, 48, 47, 47,
                46, 46, 46, 45, 45, 44, 44, 43, 43, 43, 42, 42, 41, 41, 41, 40,
                40, 40, 39, 39, 39, 38, 38, 38, 37, 37, 37, 37, 36, 36, 36, 35,
                35, 35, 35, 34, 34, 34, 34, 33, 33, 33, 33, 32, 32, 32, 32, 32,
                31, 31, 31, 31, 30, 30, 30, 30, 30, 30, 29, 29, 29, 29, 29, 28,
                28, 28, 28, 28, 28, 27, 27, 27, 27, 27, 27, 26, 26, 26, 26, 26,
                26, 25, 25, 25, 25, 25, 25, 25, 24, 24, 24, 24, 24, 24, 24, 24,
                23, 23, 23, 23, 23, 23, 23, 23, 22, 22, 22, 22, 22, 22, 22, 22,
                22, 21, 21, 21, 21, 21, 21, 21, 21, 21, 21, 20, 20, 20, 20, 20,
                20, 20, 20, 20, 20, 20, 19, 19, 19, 19, 19, 19, 19, 19, 19, 19
        };


ir_t *IR_init(apin_t pin) {
    ir_t *ir = malloc(sizeof(ir_t));

    ir->pin = pin;

    kalman_init(&IR_top_state, 1, 1, SENDER_IR); //<-- 1, 1 should be changed
    kalman_init(&IR_bottom_state, 1, 1, SENDER_IR); //<-- 1, 1 should be changed
}

void IR_calibrate(float z_0) {
    kalman_calibrate(&IR_top_state, read_top_IR()); // the 100 is Z_0, needs to be changed
    kalman_calibrate(&IR_bottom_state, read_bottom_IR()); // the 100 is Z_0, needs to be changed
}

float IR_read(ir_t *ir) {
    uint8_t IR_value = analog_read(ir->pin);
    return IR_to_cm[IR_value];
}

/*
 * SAVED FOR ANOTHER TIME; DO NOT DELETE
 * /
/*
float IR_top_to_meters() {
    return 7881.82 * pow(IR_top_state.x_k, -1.086);
}

float IR_bottom_to_meters() {
    return 7881.82 * pow(IR_bottom_state.x_k, -1.086);
}
*/
