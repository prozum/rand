//
// Created by morell on 10/7/16.
//

#ifndef RAND_MATRIX_MATH_H
#define RAND_MATRIX_MATH_H

double** mult_mat_mat(double **m1, double **m2, uint8_t mat_size);
double** mult_mat_vec(double **m, double v[], uint8_t rows, uint8_t cols);
double** trans_matrix(double **m1, uint8_t rows, uint8_t cols);
double** add_mat_mat(double** m1, double** m2, uint8_t size);
double** sub_mat_mat(double** m1, double** m2, uint8_t size);
double** ident_mat(uint8_t id);
double* add_vec_vec(double vec1[], double vec2[], uint8_t size);
double* sub_vec_vec(double vec1[], double vec2[], uint8_t size);
double** inv_mat(double** ma1);

void mat_T(double *m);
void mat_inv(double *m);

#endif //RAND_MATRIX_MATH_H
