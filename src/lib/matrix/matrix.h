#ifndef RAND_MATRIX_MATH_H
#define RAND_MATRIX_MATH_H

#include <stdint.h>
#include <stdlib.h>
#include "core/log.h"

typedef struct matrix_s {
    uint8_t rows, columns;
    float **values;
} matrix_t;

matrix_t *mult_mat_mat(matrix_t *left_matrix, matrix_t *right_matrix);

matrix_t *mult_mat_vec(matrix_t *matrix, matrix_t *vector);

matrix_t *trans_matrix(matrix_t *matrix);

matrix_t *add_mat_mat(matrix_t *left, matrix_t *right);

matrix_t *sub_mat_mat(matrix_t *left, matrix_t *right);

matrix_t *ident_mat(uint8_t size);

matrix_t *mult_const_vec(matrix_t *vector, float k);

matrix_t *add_vec_vec(matrix_t *left_vector, matrix_t *right_vector);

matrix_t *sub_vec_vec(matrix_t *left, matrix_t *right);

matrix_t *inv_mat(matrix_t *matrix);

/*void mat_T(float *m);

void mat_inv(float *m);*/

matrix_t *matrix_constructor(uint8_t rows, uint8_t columns);

void matrix_destructor(matrix_t *matrix);

#endif //RAND_MATRIX_MATH_H
