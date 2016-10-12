#include "matrix_math.h"


double** mult_mat_mat(double **ma1, double **ma2, uint8_t mat_size) {
    //Needs size checking
    uint8_t i, j, k;

    double** res = (double **) malloc(mat_size * sizeof(double*));
    for (i = 0; i < mat_size; ++i) {
        res[i] = (double *) malloc(mat_size * sizeof(double));
    }
    for (i = 0; i < mat_size; ++i) {
        for (j = 0; j < mat_size; ++j) {
            for (k = 0; k < mat_size; ++k) {
                res[j][i] += ma1[j][k] * ma2[k][i];
            }
        }
    }
    return res;
}

double** trans_matrix(double **ma1, uint8_t rows, uint8_t cols){
    uint8_t i, j;

    double** res = (double **) malloc(cols * sizeof(double*));
    for (i = 0; i < rows; i++) {
        res[i] = (double *) malloc(rows * sizeof(double));
    }

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res[i][j] = ma1[j][i];
        }
    }
    return res;
}

double* mult_mat_vec(double **ma1, double vec1[], uint8_t rows, uint8_t cols){
    uint8_t i, j;
    double* res = malloc(cols * sizeof(double));
    //Needs checks for sizes
    for (i = 0; i < rows; ++i) {
        res[i] = 0;
        for (j = 0; j < cols; ++j) {
            res[i] += ma1[i][j] * vec1[j];
        }
    }
    return res;
}

double** add_mat_mat(double **ma1, double **ma2, uint8_t mat_size){
    uint8_t i, j;
    double** res = (double **) malloc(mat_size * sizeof(double*));
    for (i = 0; i < mat_size; ++i) {
        res[i] = (double *) malloc(mat_size * sizeof(double));
    }
    for (i = 0; i < mat_size; ++i) {
        for (j = 0; j < mat_size; ++j) {
            res[i][j] = ma1[i][j] + ma2[i][j];
        }
    }
    return res;
}

double** sub_mat_mat(double **ma1, double **ma2, uint8_t mat_size){
    uint8_t i, j;
    double** res = (double **) malloc(mat_size * sizeof(double*));
    for (i = 0; i < mat_size; ++i) {
        res[i] = (double *) malloc(mat_size * sizeof(double));
    }
    for (i = 0; i < mat_size; ++i) {
        for (j = 0; j < mat_size; ++j) {
            res[i][j] = ma1[i][j] - ma2[i][j];
        }
    }
    return res;
}

double* add_vec_vec(double vec1[], double vec2[], uint8_t size){
    uint8_t i;
    double* res = malloc(size * sizeof(double));
    for (i = 0; i < size; ++i) {
        res[i] = vec1[i] + vec2[i];
    }

    return res;
}

double* sub_vec_vec(double vec1[], double vec2[], uint8_t size){
    uint8_t i;
    double* res = malloc(size * sizeof(double));
    for (i = 0; i < size; ++i) {
        res[i] = vec1[i] - vec2[i];
    }

    return res;
}
