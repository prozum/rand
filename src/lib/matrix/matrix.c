#include <stdio.h>
#include "matrix/matrix.h"

/**
 * Multiplies two vectors
 * @param left_matrix
 * @param right_matrix
 * @return a pointer to the resulting matrix
 */
matrix_t *mult_mat_mat(matrix_t *left_matrix, matrix_t *right_matrix) {
    int i = 0, j = 0, k = 0;

    //Must be two vectors of sizes N * M and M * P
    if (left_matrix->columns != right_matrix->rows) {
        ERROR("Incorrect matrix sizes in matrix-mult.");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left_matrix->rows, right_matrix->columns);

    for (i = 0; i < left_matrix->rows; ++i) {
        for (j = 0; j < right_matrix->columns; ++j) {
            res->values[i][j] = 0;
            for (k = 0; k < left_matrix->columns; ++k) {
                res->values[i][j] += left_matrix->values[i][j] * right_matrix->values[k][j];
            }
        }
    }
    return res;
}

/**
 * Multiplies a vector by a constant
 * @param vector
 * @param k constant
 * @return a pointer to the resulting vector
 */
matrix_t *mult_const_vec(matrix_t *vector, float k) {
    int i;
    matrix_t *res = matrix_constructor(vector->rows, vector->columns);

    //Determine if the vector is a row or a column vector
    if(vector->rows > 1) {
        for (i = 0; i < vector->rows; ++i) {
            res->values[i][0] = k * vector->values[i][0];
        }
    }
    else {
        for (i = 0; i < vector->columns; ++i) {
            res->values[0][i] = k * vector->values[0][i];
        }
    }
    return res;
}


/**
 * Transpose a matrix
 * @param matrix to transpose (not changed)
 * @return a pointer to the resulting matrix
 */
matrix_t *trans_matrix(matrix_t *matrix) {
    uint8_t i, j;

    matrix_t *res = matrix_constructor(matrix->columns, matrix->rows);

    for (i = 0; i < res->rows; ++i) {
        for (j = 0; j < res->columns; ++j) {
            res->values[i][j] = matrix->values[j][i];
        }
    }
    return res;
}

/**
 * Multiplies a matrix and a vector
 * @param matrix
 * @param vector
 * @return a pointer to the resulting matrix
 */
matrix_t *mult_mat_vec(matrix_t *matrix, matrix_t *vector) {
    uint8_t i, j;

    //Determine if the parameters are of correct size
    if(matrix->columns != vector->rows){
        ERROR("mult_mat_vec: invalid mat and vec given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(matrix->rows, 1); //reslut is a row-vector

    for (i = 0; i < matrix->rows; ++i) {
        res->values[i][0] = 0;
        for (j = 0; j < matrix->columns; ++j) {
            res->values[i][0] += matrix->values[i][j] * vector->values[j][0];
        }
    }
    return res;
}

/**
 * Sums the indices of two matrices
 * @param left matrix of addition
 * @param right matrix of addition
 * @return a pointer to the resulting matrix
 */
matrix_t *add_mat_mat(matrix_t *left, matrix_t *right) {
    uint8_t i, j;

    //Determine if the matrices are the same size
    if((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("add_mat_mat: matrices of different size given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left->rows, left->columns);

    //Run over the matrices and subtract the indices.
    for (i = 0; i < left->rows; ++i) {
        for (j = 0; j < right->columns; ++j) {
            res->values[i][j] = left->values[i][j] + right->values[i][j];
        }
    }
    return res;
}

/**
 * Subtracts two matrices
 * @param left matrix of subtraction
 * @param right matrix of subtraction
 * @return a pointer to the resulting matrix
 */
matrix_t *sub_mat_mat(matrix_t *left, matrix_t *right) {
    uint8_t i, j;

    //Determine if the two matrices are the same size
    if((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("sub_mat_mat: matrices of different size given");
        return NULL;
    }

    uint8_t rows = left->rows, cols = left->columns;

    matrix_t *res = matrix_constructor(rows, cols);

    //Run through all indices and subtract
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            res->values[i][j] = left->values[i][j] - right->values[i][j];
        }
    }
    return res;
}

/**
 * Sums the values of two vectors (does not change input vectors)
 * @param left vector of addition
 * @param right vector of addition
 * @return a pointer to the resulting vector
 */
matrix_t *add_vec_vec(matrix_t *left, matrix_t *right) {
    uint8_t row, i;

    //Determine if vectors are the same size
    if((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("sub_mat_mat: matrices of different size given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left->rows, left->columns);

    //Determine if the vectors are row or column
    if(left->rows > 1) {
        for (i = 0; i < left->rows; ++i) {
            res->values[i][0] = left->values[i][0] + right->values[i][0];
        }
    } else {
        for (i = 0; i < left->columns; ++i) {
            res->values[i][0] = left->values[i][0] + right->values[i][0];
        }
    }

    return res;
}

/**
 * Subtracts two vectors (both row and column)
 * @param left vector of subtraction
 * @param right vector of subtraction
 * @return a pointer to the resulting vector.
 */
matrix_t *sub_vec_vec(matrix_t *left, matrix_t *right) {
    uint8_t row, i;

    //Determine if vectors are same size
    if((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("sub_mat_mat: matrices of different size given");
        return NULL;
    }

    //Allocate space for new matrix
    matrix_t *res = matrix_constructor(left->rows, left->columns);

    //Determine if the vectors are row or column
    if(left->rows > 1) {
        for (i = 0; i < left->rows; ++i) {
            res->values[i][0] = left->values[i][0] - right->values[i][0];
        }
    } else {
        for (i = 0; i < left->columns; ++i) {
            res->values[i][0] = left->values[i][0] - right->values[i][0];
        }
    }

    return res;
}

/**
 * Inverts a matrix.
 * @param matrix to invert (not changed)
 * @return a pointer to the inverted matrix
 */
matrix_t *inv_mat(matrix_t *matrix) {
    //Only implemented for 2x2 matrix
    const uint8_t SIZE = 2;
    if(matrix->rows != SIZE || matrix->columns != SIZE) {
        ERROR("inv_mat: only implemented on 2x2.");
    }

    uint8_t i, j;
    float det;
    float **vals = matrix->values;

    //Calculate the determinant
    det = vals[0][0] * vals[1][1] - vals[0][1] * vals[1][0];
    //Allocate space
    matrix_t *inv_mat = matrix_constructor(matrix->rows, matrix->columns);

    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            inv_mat->values[i][j] = matrix->values[i][j] / det;
            if (j != i)
                inv_mat->values[i][j] = -inv_mat->values[i][j];
        }
    }
    float temp = inv_mat->values[0][0];
    inv_mat->values[0][0] = inv_mat->values[1][1];
    inv_mat->values[1][1] = temp;
    return inv_mat;
}

matrix_t *ident_mat(uint8_t size) {
    matrix_t *res = matrix_constructor(size, size);

    uint8_t i, j;
    for(i = 0; i < size; i++) {
        for(j = 0; j < size; j++) {
            if(i == j)
                res->values[i][j] = 1;
        }
    }
}

/**
 * Allocates a new matrix for use in the matrix-library
 * @param rows of the matrix
 * @param columns of the matrix
 * @return a pointer to the allocated matrix
 */
matrix_t *matrix_constructor(uint8_t rows, uint8_t columns) {
    uint8_t i;
    matrix_t *new_matrix = malloc(sizeof(matrix_t));
    new_matrix->rows = rows;
    new_matrix->columns = columns;

    new_matrix->values = malloc(rows * sizeof(float*));
    for (i = 0; i <= rows; i++) {
        new_matrix->values[i] = malloc(columns * sizeof(float));
    }

    if(!new_matrix || new_matrix->values)
        ERROR("mat_const: failed to allocate a matrix.");

    return new_matrix;
}

/***
 * Frees an allocated matrix and its associated values.
 * @param matrix to free
 */
void matrix_destructor(matrix_t *matrix) {
    uint8_t i;
    for (i = 0; i < matrix->rows; ++i) {
        free(matrix->values[i]);
    }
    free(matrix->values);
    free(matrix);
}