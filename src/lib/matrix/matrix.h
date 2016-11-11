#ifndef RAND_MATRIX_MATH_H
#define RAND_MATRIX_MATH_H

#include <stdint.h>
#include <stdlib.h>

float** mult_mat_mat(float **m1, float **m2, uint8_t ma1_rows, uint8_t ma1_columns, uint8_t ma2_rows, uint8_t ma2_columns);
float** mult_mat_vec(float **m, float **v, uint8_t rows, uint8_t cols);
float** trans_matrix(float **m1, uint8_t rows, uint8_t cols);
float** add_mat_mat(float** m1, float** m2, uint8_t size);
float** sub_mat_mat(float** m1, float** m2, uint8_t size);
float** ident_mat(uint8_t id);
float** mult_const_vec(float** vec1, float k, uint8_t rows);
float** add_vec_vec(float** vec1, float** vec2, uint8_t size);
float** sub_vec_vec(float** vec1, float** vec2, uint8_t size);
float** inv_mat(float** ma1);

void mat_T(float *m);
void mat_inv(float *m);

#endif //RAND_MATRIX_MATH_H
