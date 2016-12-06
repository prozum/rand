#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

#include <stdlib.h>

extern "C" {
#include "matrix/matrix.h"
#include "libfixmath/fix16.h"
};

class MatrixTest : public CppUnit::TestCase {
        CPPUNIT_TEST_SUITE(MatrixTest);
        CPPUNIT_TEST(matrix_get_1x1_ExpectCorrect);
        CPPUNIT_TEST(matrix_get_1x2_ExpectCorrect);
        CPPUNIT_TEST(matrix_get_2x1_ExpectCorrect);
        CPPUNIT_TEST(matrix_get_2x2_ExpectCorrect);
        CPPUNIT_TEST(matrix_get_3x3_ExpectCorrect);

        CPPUNIT_TEST(matrix_set_1x1_ExpectCorrect);
        CPPUNIT_TEST(matrix_set_1x2_ExpectCorrect);
        CPPUNIT_TEST(matrix_set_2x1_ExpectCorrect);
        CPPUNIT_TEST(matrix_set_2x2_ExpectCorrect);
        CPPUNIT_TEST(matrix_set_3x3_ExpectCorrect);

        CPPUNIT_TEST(mult_mat_mat_ValidMatrix_ExpectCorrect);
        CPPUNIT_TEST(mult_mat_mat_InvalidMatrix_ExpectError);
        CPPUNIT_TEST(mult_mat_mat_DifferentSizes_ExpectCorrect);

        CPPUNIT_TEST(trans_matrix_SquareMatrix_ExpectTransposed);
        CPPUNIT_TEST(trans_matrix_NotSquareMatrix_ExpectTransposed);

        CPPUNIT_TEST(add_mat_mat_ValidMatrix_ExpectCorrect);
        CPPUNIT_TEST(add_mat_mat_InvalidMatrix_ExpectError);
        CPPUNIT_TEST(sub_mat_mat_ValidMatrix_ExpectCorrect);
        CPPUNIT_TEST(sub_mat_mat_InvalidMatrix_ExpectError);

        CPPUNIT_TEST(ident_mat_ExpectCorrect);

        CPPUNIT_TEST(add_vec_vec_ValidVectors_ExpectCorrect);
        CPPUNIT_TEST(add_vec_vec_EmptyVector_ExpectError);

        CPPUNIT_TEST(sub_vec_Vec_ValidVectors_ExpectCorrect);
        CPPUNIT_TEST(sub_vec_vec_EmptyVectors_ExpectError);

        CPPUNIT_TEST(inv_mat_ValidMatrix_ExpectCorrect);
        CPPUNIT_TEST(inv_mat_InvalidMatrix_ExpectError);
        CPPUNIT_TEST_SUITE_END();
private:
    matrix_t *ma1, *ma2, *ma3, *ma4, *vec, *vecEmpty;

    void setUp_mat1();
    void setup_mat2();
    void setup_mat3();
    void setup_mat4();
    void setup_vec();
public:
    void setUp();

    void tearDown();

    void mult_mat_mat_ValidMatrix_ExpectCorrect();

    void mult_mat_mat_InvalidMatrix_ExpectError();

    void mult_mat_mat_DifferentSizes_ExpectCorrect();

    void trans_matrix_SquareMatrix_ExpectTransposed();

    void trans_matrix_NotSquareMatrix_ExpectTransposed();

    void add_mat_mat_ValidMatrix_ExpectCorrect();

    void add_mat_mat_InvalidMatrix_ExpectError();

    void sub_mat_mat_ValidMatrix_ExpectCorrect();

    void sub_mat_mat_InvalidMatrix_ExpectError();

    void ident_mat_ExpectCorrect();

    void add_vec_vec_ValidVectors_ExpectCorrect();

    void add_vec_vec_EmptyVector_ExpectError();

    void sub_vec_Vec_ValidVectors_ExpectCorrect();

    void sub_vec_vec_EmptyVectors_ExpectError();

    void inv_mat_ValidMatrix_ExpectCorrect();

    void inv_mat_InvalidMatrix_ExpectError();

    void matrix_get_1x1_ExpectCorrect();
    void matrix_get_2x2_ExpectCorrect();
    void matrix_get_1x2_ExpectCorrect();
    void matrix_get_2x1_ExpectCorrect();
    void matrix_get_3x3_ExpectCorrect();

    void matrix_set_1x1_ExpectCorrect();
    void matrix_set_2x2_ExpectCorrect();
    void matrix_set_1x2_ExpectCorrect();
    void matrix_set_2x1_ExpectCorrect();
    void matrix_set_3x3_ExpectCorrect();
};