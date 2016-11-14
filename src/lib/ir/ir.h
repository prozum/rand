#ifndef RAND_IR_H
#define RAND_IR_H

#define IR_TOP_PIN 1
#define IR_BOTTOM_PIN 2

void IR_init();

float read_top_IR();

float read_bottom_IR();

float IR_top_to_meters();

float IR_bottom_to_meters();

void IR_calibrate(float z_0);

#endif //RAND_IR_H
