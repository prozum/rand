#ifndef RAND_MATRIX_MATH_H
#define RAND_MATRIX_MATH_H

#include <stdint.h>
#include <stdlib.h>
#include "core/log.h"
#include "libfixmath/fix16.h"

typedef struct matrix_s {
    uint8_t rows, columns;
    fix16_t *values;
} matrix_t;

/**
 * Multiplies two matrices
 * @param left_matrix
 * @param right_matrix
 * @return
 */
matrix_t *mult_mat_mat(matrix_t *left_matrix, matrix_t *right_matrix);
/**
 * Multiplies a matrix with a vector
 * @param matrix
 * @param vector
 * @return
 */
matrix_t *mult_mat_vec(matrix_t *matrix, matrix_t *vector);
/**
 * Translates a matrix
 * @param matrix
 * @return
 */
matrix_t *trans_matrix(matrix_t *matrix);
/**
 * Adds the indices of two matrices
 * @param left
 * @param right
 * @return
 */
matrix_t *add_mat_mat(matrix_t *left, matrix_t *right);
/**
 * Subtracts the indices of two matrices
 * @param left
 * @param right
 * @return
 */
matrix_t *sub_mat_mat(matrix_t *left, matrix_t *right);
/**
 * Produces the identity matrix of a specified size
 * @param size - Width and height of the desired identity matrix
 * @return
 */
matrix_t *ident_mat(uint8_t size);
/**
 * Multiplies the indices of a vector with a constant
 * @param vector
 * @param k
 * @return
 */
matrix_t *mult_const_vec(matrix_t *vector, fix16_t k);
/**
 * Sums the indices of two vectors
 * @param left_vector
 * @param right_vector
 * @return
 */
matrix_t *add_vec_vec(matrix_t *left_vector, matrix_t *right_vector);
/**
 * Subtracts the indices of two vectors
 * @param left
 * @param right
 * @return
 */
matrix_t *sub_vec_vec(matrix_t *left, matrix_t *right);
/**
 * Finds the inverse of a specified matrix
 * @param matrix
 * @return
 */
matrix_t *inv_mat(matrix_t *matrix);
/**
 * Constructs a new rows x columns matrix
 * @param rows - Rows of the new matrix
 * @param columns - Columns of the new matrix
 * @return - A pointer to the newly allocated matrix
 */
matrix_t *matrix_constructor(uint8_t rows, uint8_t columns);
/**
 * Deallocates a matrix
 * @param matrix - A pointer to the matrix to deallocate - DO NOT USE THIS AFTERWARDS
 */
void matrix_destructor(matrix_t *matrix);
/**
 * Sets the given index of the matrix to the specified value
 * @param matrix - A pointer to the matrix to update
 * @param row - The row-index
 * @param column - The columns-index
 * @param value - The value to set to the specified index
 */
void matrix_set(matrix_t *matrix, uint8_t row, uint8_t column, fix16_t value);
/**
 * Gets the value of the specified index
 * @param matrix - A pointer to the matrix to get from
 * @param row - The row-index
 * @param column - The column-index
 * @return - The value found in specified index
 */
fix16_t matrix_get(matrix_t *matrix, uint8_t row, uint8_t column);

#endif //RAND_MATRIX_MATH_H
