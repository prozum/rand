#include "matrix_math/matrix_math.h"


/*double** mult_mat_mat(double **ma1, double **ma2, uint8_t mat_size) {
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
}*/

double** mult_mat_mat(double **ma1, double **ma2, uint8_t ma1_rows, uint8_t ma1_columns, uint8_t ma2_rows, uint8_t ma2_columns) {
    int i = 0, j = 0, k = 0;

    if(ma1_columns != ma2_rows){
        //Error write to log
        return NULL;
    }

    double res[ma1_rows][ma2_columns]; //Necessary because of weird bug with pres overriding values in ma1 when allocated.

    for (i = 0; i < ma1_rows; ++i) {
        for (j = 0; j < ma2_columns; ++j) {
            res[i][j] = 0;
            for (k = 0; k < ma1_columns; ++k) {
                res[i][j] += ma1[i][k] * ma2[k][j];
            }
        }
    }

    double** pres = malloc(ma2_columns * sizeof(double*));
    for (i = 0; i < ma2_columns; ++i) {
        pres[i] = (double *) malloc(ma1_rows * sizeof(double));
    }

    for (i = 0; i < ma1_rows; ++i) {
        for (j = 0; j < ma2_columns; ++j) {
            pres[i][j] = res[i][j];
        }
    }
    return pres;
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

double** inv_mat(double** ma1){
    //Only functions with a simple 2x2 matrix
    int i, j;
    double det;

    det = ma1[0][0]*ma1[1][1]-ma1[0][1]*ma1[1][0];

    double** in_mat = (double **) malloc(2 * sizeof(double*));

    for (i = 0; i < 2; ++i) {
        in_mat[i] = (double *) malloc(2 * sizeof(double));
    }

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            in_mat[i][j] = ma1[i][j]/det;
            if(j != i)
                in_mat[i][j] = -in_mat[i][j];
        }
    }
    double temp = in_mat[0][0];
    in_mat[0][0] = in_mat[1][1];
    in_mat[1][1] = temp;
    return in_mat;
}