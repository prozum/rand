//
// Created by morell on 10/7/16.
//

#ifndef RAND_MATRIX_MATH_H
#define RAND_MATRIX_MATH_H

void mult_mat_mat(double *m1, double *m2, uint8_t mat_size);
void mult_mat_vec(double *m, double *v);
void mat_T(double *m);
void mat_inv(double *m);

#endif //RAND_MATRIX_MATH_H
