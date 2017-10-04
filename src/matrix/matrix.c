#include "matrix/matrix.h"

#include <stdio.h>

/**
 * Multiplies two vectors
 * @param left_matrix
 * @param right_matrix
 * @return a pointer to the resulting matrix
 */
matrix_t *mult_mat_mat(matrix_t *left_matrix, matrix_t *right_matrix) {
    uint8_t i = 0, j = 0, k = 0;

    // Must be two vectors of sizes N * M and M * P
    if (left_matrix->columns != right_matrix->rows) {
        ERROR("Incorrect matrix sizes in matrix-mult.");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left_matrix->rows, right_matrix->columns);

    fix16_t result;
    for (i = 0; i < left_matrix->rows; ++i) {
        for (j = 0; j < right_matrix->columns; ++j) {
            result = fix16_from_int(0);
            for (k = 0; k < left_matrix->columns; ++k) {
                result = fix16_add(result, fix16_mul(matrix_get(left_matrix, i, k), matrix_get(right_matrix, k, j)));
            }
            matrix_set(res, i, j, result);
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
matrix_t *mult_const_vec(matrix_t *vector, fix16_t k) {
    uint8_t i;
    matrix_t *res = matrix_constructor(vector->rows, vector->columns);

    // Determine if the vector is a row or a column vector
    if (vector->rows > 1) {
        for (i = 0; i < vector->rows; ++i) {
            fix16_t mul_res = fix16_mul(k, matrix_get(vector, i, 0));
            matrix_set(res, i, 0, mul_res);
        }
    } else {
        for (i = 0; i < vector->columns; ++i) {
            fix16_t mul_res = fix16_mul(k, matrix_get(vector, 0, i));
            matrix_set(res, 0, i, mul_res);
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
            matrix_set(res, i, j, matrix_get(matrix, j, i));
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

    // Determine if the parameters are of correct size
    if (matrix->columns != vector->rows) {
        ERROR("mult_mat_vec: invalid mat and vec given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(matrix->rows, 1); // reslut is a row-vector

    for (i = 0; i < matrix->rows; ++i) {
        matrix_set(res, i, 0, 0);
        for (j = 0; j < matrix->columns; ++j) {
            // res[i, 0] += mat[i, j] * vec[j, 0]
            fix16_t mul_res =
                fix16_add(matrix_get(res, i, 0), fix16_mul(matrix_get(matrix, i, j), matrix_get(vector, j, 0)));
            matrix_set(res, i, 0, mul_res);
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

    // Determine if the matrices are the same size
    if ((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("add_mat_mat: matrices of different size given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left->rows, left->columns);

    // Run over the matrices and subtract the indices.
    for (i = 0; i < left->rows; ++i) {
        for (j = 0; j < right->columns; ++j) {
            fix16_t add_res = fix16_add(matrix_get(left, i, j), matrix_get(right, i, j));
            matrix_set(res, i, j, add_res);
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

    // Determine if the two matrices are the same size
    if ((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("sub_mat_mat: matrices of different size given");
        return NULL;
    }

    uint8_t rows = left->rows, cols = left->columns;

    matrix_t *res = matrix_constructor(rows, cols);

    // Run through all indices and subtract
    for (i = 0; i < rows; ++i) {
        for (j = 0; j < cols; ++j) {
            fix16_t sub_res = fix16_sub(matrix_get(left, i, j), matrix_get(right, i, j));
            matrix_set(res, i, j, sub_res);
        }
    }
    return res;
}

matrix_t *add_vec_vec(matrix_t *left, matrix_t *right) {
    uint8_t i;

    if (!left || !right) {
        ERROR("A null-vector was given to add_vec_ved");
        return NULL;
    }

    // Determine if vectors are the same size
    if ((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("add_vec_vec: vectors of different size given");
        return NULL;
    }

    matrix_t *res = matrix_constructor(left->rows, left->columns);

    // Determine if the vectors are row or column
    if (left->rows > 1) {
        for (i = 0; i < left->rows; ++i) {
            fix16_t add_res = fix16_add(matrix_get(left, i, 0), matrix_get(right, i, 0));
            matrix_set(res, i, 0, add_res);
        }
    } else {
        for (i = 0; i < left->columns; ++i) {
            fix16_t add_res = fix16_add(matrix_get(left, 0, i), matrix_get(right, 0, i));
            matrix_set(res, 0, i, add_res);
        }
    }

    return res;
}

matrix_t *sub_vec_vec(matrix_t *left, matrix_t *right) {
    uint8_t i;

    if (!left || !right) {
        ERROR("sub_vec_vec received NULL-vector");
        return NULL;
    }

    // Determine if vectors are same size
    if ((left->columns != right->columns) || (left->rows != right->rows)) {
        ERROR("sub_mat_mat: matrices of different size given");
        return NULL;
    }

    // Allocate space for new matrix
    matrix_t *res = matrix_constructor(left->rows, left->columns);

    // Determine if the vectors are row or column
    if (left->rows > 1) {
        for (i = 0; i < left->rows; ++i) {
            fix16_t sub_res = fix16_sub(matrix_get(left, i, 0), matrix_get(right, i, 0));
            matrix_set(res, i, 0, sub_res);
        }
    } else {
        for (i = 0; i < left->columns; ++i) {
            fix16_t sub_res = fix16_sub(matrix_get(left, 0, i), matrix_get(right, 0, i));
            matrix_set(res, 0, i, sub_res);
        }
    }

    return res;
}

matrix_t *inv_mat(matrix_t *matrix) {
    // Only implemented for 2x2 matrix
    const uint8_t SIZE = 2;
    if (matrix->rows != SIZE || matrix->columns != SIZE) {
        ERROR("inv_mat: only implemented on 2x2.");
        return NULL;
    }

    uint8_t i, j;

    // Calculate the determinant
    fix16_t det;
    det = fix16_sub(fix16_mul(matrix_get(matrix, 0, 0), matrix_get(matrix, 1, 1)),
                    fix16_mul(matrix_get(matrix, 1, 0), matrix_get(matrix, 0, 1)));
    // Allocate space
    matrix_t *inv_mat = matrix_constructor(matrix->rows, matrix->columns);

    for (i = 0; i < SIZE; ++i) {
        for (j = 0; j < SIZE; ++j) {
            matrix_set(inv_mat, i, j, fix16_div(matrix_get(matrix, i, j), det));
            if (j != i)
                matrix_set(inv_mat, i, j,
                           -matrix_get(inv_mat, i, j)); // The libfixmath supports directly - with out function call
        }
    }
    fix16_t temp = matrix_get(inv_mat, 0, 0);
    matrix_set(inv_mat, 0, 0, matrix_get(inv_mat, 1, 1));
    matrix_set(inv_mat, 1, 1, temp);
    return inv_mat;
}

matrix_t *ident_mat(uint8_t size) {
    matrix_t *res = matrix_constructor(size, size);

    uint8_t i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (i == j)
                matrix_set(res, i, j, fix16_from_int(1));
            else
                matrix_set(res, i, j, fix16_from_int(0));
        }
    }

    return res;
}

matrix_t *matrix_constructor(uint8_t rows, uint8_t columns) {
    matrix_t *new_matrix = malloc(sizeof(matrix_t));
    new_matrix->rows = rows;
    new_matrix->columns = columns;

    new_matrix->values = malloc(columns * rows * sizeof(fix16_t));

    if (!new_matrix || !new_matrix->values)
        ERROR("mat_const: failed to allocate a matrix.");

    return new_matrix;
}

/***
 * Frees an allocated matrix and its associated values.
 * @param matrix to free
 */
void matrix_destructor(matrix_t *matrix) {
    free(matrix->values);
    free(matrix);
}

void matrix_set(matrix_t *matrix, uint8_t row, uint8_t column, fix16_t value) {
    if (!matrix) {
        ERROR("matrix_set: null-matrix");
        return;
    }

    if (row >= matrix->rows || column >= matrix->columns) {
        ERROR("Matrix index is out of bounds.");
        return;
    }

    matrix->values[row * matrix->columns + column] = value;
}

fix16_t matrix_get(matrix_t *matrix, uint8_t row, uint8_t column) {
    if (!matrix) {
        ERROR("Null-matrix parameter in getter");
        return -1;
    }

    if (row >= matrix->rows || column >= matrix->columns) {
        ERROR("Matrix index is out of bounds");
        return -1;
    }

    return matrix->values[row * matrix->columns + column];
}