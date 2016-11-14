#include "matrix/matrix.h"


/*float** mult_mat_mat(float **ma1, float **ma2, uint8_t mat_size) {
    //Needs size checking
    uint8_t i, j, k;

    float** res = (float **) malloc(mat_size * sizeof(float*));
    for (i = 0; i < mat_size; ++i) {
        res[i] = (float *) malloc(mat_size * sizeof(float));
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

float **
mult_mat_mat(float **ma1, float **ma2, uint8_t ma1_rows, uint8_t ma1_columns, uint8_t ma2_rows, uint8_t ma2_columns) {
    int i = 0, j = 0, k = 0;

    if (ma1_columns != ma2_rows) {
        //Error write to log
        return NULL;
    }

    float **res = malloc(ma2_columns * sizeof(float *));
    for (i = 0; i < ma2_columns; ++i) {
        res[i] = (float *) malloc(ma1_rows * sizeof(float *));
        for (j = 0; j < ma1_rows; j++) {
            res[j] = (float *) malloc(sizeof(float));
        }
    }

    for (i = 0; i < ma1_rows; ++i) {
        for (j = 0; j < ma2_columns; ++j) {
            res[i][j] = 0;
            for (k = 0; k < ma1_columns; ++k) {
                res[i][j] += ma1[i][k] * ma2[k][j];
            }
        }
    }
    return res;
}

float **mult_const_vec(float **vec1, float k, uint8_t rows) {
    int i;
    float **res = malloc(rows * sizeof(float *));

    for (i = 0; i < rows; i++) {
        res[i] = (float *) malloc(sizeof(float));
    }

    for (i = 0; i < rows; ++i) {
        res[i][0] = k * vec1[i][0];
    }
    return res;
}

float **trans_matrix(float **ma1, uint8_t rows, uint8_t cols) {
    uint8_t i, j;

    float **res = (float **) malloc(rows * sizeof(float *));
    for (i = 0; i < rows; i++) {
        res[i] = (float *) malloc(cols * sizeof(float));
    }

    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res[i][j] = ma1[j][i];
        }
    }
    return res;
}

float **mult_mat_vec(float **ma1, float **vec1, uint8_t rows, uint8_t cols) {
    uint8_t i, j;
    float **res = malloc(cols * sizeof(float));

    for (i = 0; i < cols; i++) {
        res[i] = (float *) malloc(sizeof(float));
    }

    for (i = 0; i < rows; ++i) {
        res[i] = 0;
        for (j = 0; j < cols; ++j) {
            res[i][0] += ma1[i][j] * vec1[j][0];
        }
    }
    return res;
}

float **add_mat_mat(float **ma1, float **ma2, uint8_t mat_size) {
    uint8_t i, j;
    float **res = (float **) malloc(mat_size * sizeof(float *));

    for (i = 0; i < mat_size; ++i) {
        res[i] = (float *) malloc(mat_size * sizeof(float));
    }

    for (i = 0; i < mat_size; ++i) {
        for (j = 0; j < mat_size; ++j) {
            res[i][j] = ma1[i][j] + ma2[i][j];
        }
    }
    return res;
}

float **sub_mat_mat(float **ma1, float **ma2, uint8_t mat_size) {
    uint8_t i, j;
    float **res = (float **) malloc(mat_size * sizeof(float *));

    for (i = 0; i < mat_size; ++i) {
        res[i] = (float *) malloc(mat_size * sizeof(float));
    }

    for (i = 0; i < mat_size; ++i) {
        for (j = 0; j < mat_size; ++j) {
            res[i][j] = ma1[i][j] - ma2[i][j];
        }
    }
    return res;
}

float **add_vec_vec(float **vec1, float **vec2, uint8_t size) {
    uint8_t row, i;
    float **res = malloc(size * sizeof(float *));
    for (row = 0; row < size; row++) {
        res[row] = (float *) malloc(sizeof(float));
    }

    for (i = 0; i < size; ++i) {
        res[i][0] = vec1[i][0] + vec2[i][0];
    }

    return res;
}

float **sub_vec_vec(float **vec1, float **vec2, uint8_t size) {
    uint8_t i;
    float **res = malloc(size * sizeof(float *));
    for (i = 0; i < size; i++) {
        res[i] = (float *) malloc(sizeof(float));
    }
    for (i = 0; i < size; ++i) {
        res[i][0] = vec1[i][0] - vec2[i][0];
    }

    return res;
}

float **inv_mat(float **ma1) {
    //Only functions with a simple 2x2 matrix
    int i, j;
    float det;

    det = ma1[0][0] * ma1[1][1] - ma1[0][1] * ma1[1][0];

    float **in_mat = (float **) malloc(2 * sizeof(float *));

    for (i = 0; i < 2; ++i) {
        in_mat[i] = (float *) malloc(2 * sizeof(float));
    }

    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            in_mat[i][j] = ma1[i][j] / det;
            if (j != i)
                in_mat[i][j] = -in_mat[i][j];
        }
    }
    float temp = in_mat[0][0];
    in_mat[0][0] = in_mat[1][1];
    in_mat[1][1] = temp;
    return in_mat;
}