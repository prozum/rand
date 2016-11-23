#include "matrix_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp() {
    float mat1[3][3] = {{9.1, 6.0, 2.8},
                        {7.4, 1.0, 3.0},
                        {4.5, 0.0, 8.0}};
    float mat2[3][3] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0}};
    float mat3[2][2] = {{32.1, 8.3},
                        {0.72, 43.7}};
    float mat4[3][2] = {{1, 2},
                        {3, 4},
                        {5, 6}};

    vec1 = (float **) malloc(3 * sizeof(float *));
    for (int k = 0; k < 3; ++k) {
        vec1[k] = (float *) malloc(sizeof(float));
    }
    vec1[0][0] = 1;
    vec1[1][0] = 2;
    vec1[2][0] = 1;

    int size = 3, row, col, i, j;
    ma1 = (float **) malloc(size * sizeof(float *));
    ma2 = (float **) malloc(size * sizeof(float *));
    ma3 = (float **) malloc(size * sizeof(float *));
    ma4 = (float **) malloc(size * sizeof(float *));


    //Allocating space for second dimension
    for (row = 0; row < size; ++row) {
        ma1[row] = (float *) malloc(size * sizeof(float));
    }
    for (row = 0; row < size; ++row) {
        ma2[row] = (float *) malloc(size * sizeof(float));
    }
    for (row = 0; row < 2; ++row) {
        ma3[row] = (float *) malloc(2 * sizeof(float));
    }
    for (row = 0; row < 2; ++row) {
        ma4[row] = (float *) malloc(3 * sizeof(float));
    }

    //Setting values to test values from mat1 and 4
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            ma1[row][col] = mat1[row][col];
        }
    }

    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            ma2[row][col] = mat2[row][col];
        }
    }
    for (row = 0; row < 2; ++row) {
        for (col = 0; col < 2; ++col) {
            ma3[row][col] = mat3[row][col];
        }
    }
    for (row = 0; row < 3; ++row) {
        for (col = 0; col < 2; ++col) {
            ma4[row][col] = mat4[row][col];
        }
    }
}

void MatrixTest::tearDown() {
    delete ma1;
    delete ma2;
    delete ma3;
    delete ma4;
    delete vecEmpty;
}

void MatrixTest::mult_mat_mat_ValidMatrix_ExpectCorrect() {
    double **resMat;
    //double **resMat = mult_mat_mat(ma1, ma2, 3, 3, 3, 3);
    double ResMulMat3x3[3][3] = {{52.7, 70.6, 88.5},
                                 {32.4, 43.8, 55.2},
                                 {60.5, 73.0, 85.5}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMulMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::mult_mat_mat_InvalidMatrix_ExpectError() {
    double **resMat;
    //double **resMat = mult_mat_mat(ma1, ma3, 3, 3, 2, 2);
    double ResMulMat3x3[3][3] = {{52.7, 70.6, 88.5},
                                 {32.4, 43.8, 55.2},
                                 {60.5, 73.0, 85.5}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMulMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::mult_mat_mat_DifferentSizes_ExpectCorrect() {
    float **resMat;
    //resMat = mult_mat_mat(ma1, ma4, 3, 3, 3, 2);
    float ResMulMat[3][2] = {{41.1, 59},
                             {25.4, 36.8},
                             {62.5, 81}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (ResMulMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_SquareMatrix_ExpectTransposed() {
    double ResTransMat[3][3] = {{1, 4, 7},
                                {2, 5, 8},
                                {3, 6, 9}};
    double **resMat;
    //double **resMat = trans_matrix(ma2);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResTransMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_NotSquareMatrix_ExpectTransposed() {
    double ResTransMat[3][3] = {{1, 3, 5},
                                {2, 4, 6}};
    double **resMat;
    //double **resMat = trans_matrix(ma4);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (ResTransMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_mat_mat_ValidMatrix_ExpectCorrect() {
    double **resMat;
    //double **resMat = add_mat_mat(ma1, ma2);
    double ResAddMat3x3[3][3] = {{10.1, 8, 5.8},
                                 {11.4, 6, 9},
                                 {11.5, 8, 17}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResAddMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::add_mat_mat_InvalidMatrix_ExpectError() {
    double **resMat;
    //double **resMat = add_mat_mat(ma1, ma3);
    double ResAddMat3x3[3][3] = {{10.1, 8, 5.8},
                                 {11.4, 6, 9},
                                 {11.5, 8, 17}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResAddMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_ValidMatrix_ExpectCorrect() {
    double **resMat;
    //double **resMat = sub_mat_mat(ma1, ma2);
    double ResSubMat3x3[3][3] = {{8.1,  4,  -0.2},
                                 {3.4,  -4, -3},
                                 {-2.5, -8, -1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResSubMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_InvalidMatrix_ExpectError() {
    double **resMat;
    //double **resMat = sub_mat_mat(ma1, ma3);
    double ResSubMat3x3[3][3] = {{8.1,  4,  -0.2},
                                 {3.4,  -4, -3},
                                 {-2.5, -8, -1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResSubMat3x3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::ident_mat_ExpectCorrect() {
    double **resMat;
    //double **resMat = ident_mat(3);
    double ResIdentMat3[3][3] = {{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResIdentMat3[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_ValidVectors_ExpectCorrect() {
    float **ResVec = add_vec_vec(vec1, vec1, 3);

    double ResAddVec[] = {2, 4, 2};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResAddVec[i] != ResVec[0][i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_EmptyVector_ExpectError() {
    float ResAddVec[] = {2, 4, 2};

    float **ResVec = add_vec_vec(vec1, vecEmpty, 3);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResAddVec[i] != ResVec[0][i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_vec_Vec_ValidVectors_ExpectCorrect() {
    float ResSubVec[] = {0, 0, 0};

    float **ResVec = sub_vec_vec(vec1, vec1, 3);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResSubVec[i] != ResVec[0][i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::sub_vec_vec_EmptyVectors_ExpectError() {
    float ResSubVec[] = {0, 0, 0};
    float **ResVec = sub_vec_vec(vec1, vecEmpty, 3);

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResSubVec[i] != ResVec[0][i])
            IsEqual = false;
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::inv_mat_ValidMatrix_ExpectCorrect() {
    double **resMat, InvMat[3][3] = {{1, 2, 3},
                                     {0, 1, 4},
                                     {5, 6, 0}}, **matToInv;

    matToInv = (double **) malloc(3 * sizeof(double *));
    for (int i = 0; i < 3; ++i) {
        matToInv[i] = (double *) malloc(3 * sizeof(double));
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matToInv[i][j] = InvMat[i][j];
        }
    }

    //resMat = inv_mat(matToInv);
    double ResMat[3][3] = {{-24, 18,  5},
                           {20,  -15, -4},
                           {-5,  4,   1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMat[i][j] != resMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::inv_mat_InvalidMatrix_ExpectError() {
    double **actualResMat, ResMat[3][3] = {{-24, 18,  5},
                                           {20,  -15, -4},
                                           {-5,  4,   1}};

    //double **actualResMat = inv_mat(ma2);

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMat[i][j] != actualResMat[i][j])
                IsEqual = false;
        }
    }
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}
