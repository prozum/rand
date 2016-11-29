#include "matrix_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp_mat1() {
    float mat[3][3] = {{9.1, 6.0, 2.8},
                        {7.4, 1.0, 3.0},
                        {4.5, 0.0, 8.0}};
    for (int i = 0; i < ma1->rows; ++i) {
        for (int j = 0; j < ma1->columns; ++j) {
            ma1->values[i][j] = mat[i][j];
        }
    }
}

void MatrixTest::setup_mat2() {
    float mat[3][3] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0}};
    for (int i = 0; i < ma2->rows; ++i) {
        for (int j = 0; j < ma2->columns; ++j) {
            ma2->values[i][j] = mat[i][j];
        }
    }
}

void MatrixTest::setup_mat3() {
    float mat[2][2] = {{32.1, 8.3},
                        {0.72, 43.7}};
    for (int i = 0; i < ma3->rows; ++i) {
        for (int j = 0; j < ma3->columns; ++j) {
            ma3->values[i][j] = mat[i][j];
        }
    }

}

void MatrixTest::setup_mat4() {
    float mat[3][2] = {{1, 2},
                        {3, 4},
                        {5, 6}};

    for (int i = 0; i < ma4->rows; ++i) {
        for (int j = 0; j < ma4->columns; ++j) {
            ma4->values[i][j] = mat[i][j];
        }
    }
}

void MatrixTest::setup_vec() {
    float ve[3][1] = {{1} , {2}, {1}};

    for (int i = 0; i < vec->columns; ++i) {
        vec->values[i][0] = ve[i][0];
    }
}

void MatrixTest::setUp() {
    ma1 = matrix_constructor(3, 3);
    setUp_mat1();
    ma2 = matrix_constructor(3, 3);
    setup_mat2();
    ma3 = matrix_constructor(2, 2);
    setup_mat3();
    ma4 = matrix_constructor(3, 2);
    setup_mat4();

    vec = matrix_constructor(3, 1);
    setup_vec();
}

void MatrixTest::tearDown() {
    delete ma1;
    delete ma2;
    delete ma3;
    delete ma4;
    delete vecEmpty;
}

void MatrixTest::mult_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat = mult_mat_mat(ma1, ma2);
    //double **resMat = mult_mat_mat(ma1, ma2, 3, 3, 3, 3);
    float ResMulMat3x3[3][3] = {{52.7, 70.6, 88.5},
                                 {32.4, 43.8, 55.2},
                                 {60.5, 73.0, 85.5}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMulMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);

    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::mult_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = mult_mat_mat(ma1, ma3);
    //double **resMat = mult_mat_mat(ma1, ma3, 3, 3, 2, 2);
    double ResMulMat3x3[3][3] = {{52.7, 70.6, 88.5},
                                 {32.4, 43.8, 55.2},
                                 {60.5, 73.0, 85.5}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMulMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::mult_mat_mat_DifferentSizes_ExpectCorrect() {
    matrix_t *resMat;
    //resMat = mult_mat_mat(ma1, ma4, 3, 3, 3, 2);
    float ResMulMat[3][2] = {{41.1, 59},
                             {25.4, 36.8},
                             {62.5, 81}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (ResMulMat[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_SquareMatrix_ExpectTransposed() {
    float ResTransMat[3][3] = {{1, 4, 7},
                                {2, 5, 8},
                                {3, 6, 9}};
    matrix_t *resMat = trans_matrix(ma2);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResTransMat[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::trans_matrix_NotSquareMatrix_ExpectTransposed() {
    float ResTransMat[3][3] = {{1, 3, 5},
                                {2, 4, 6}};
    matrix_t *resMat = trans_matrix(ma4);

    bool IsEqual = true;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (ResTransMat[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat = add_mat_mat(ma1, ma2);
    float ResAddMat3x3[3][3] = {{10.1, 8, 5.8},
                                 {11.4, 6, 9},
                                 {11.5, 8, 17}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResAddMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::add_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = add_mat_mat(ma1, ma3);
    float ResAddMat3x3[3][3] = {{10.1, 8, 5.8},
                                 {11.4, 6, 9},
                                 {11.5, 8, 17}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResAddMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat;
    //double **resMat = sub_mat_mat(ma1, ma2);
    float ResSubMat3x3[3][3] = {{8.1,  4,  -0.2},
                                 {3.4,  -4, -3},
                                 {-2.5, -8, -1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResSubMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = sub_mat_mat(ma1, ma3);
    float ResSubMat3x3[3][3] = {{8.1,  4,  -0.2},
                                 {3.4,  -4, -3},
                                 {-2.5, -8, -1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResSubMat3x3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::ident_mat_ExpectCorrect() {
    matrix_t *resMat = ident_mat(3);
    float ResIdentMat3[3][3] = {{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResIdentMat3[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_ValidVectors_ExpectCorrect() {
    matrix_t *ResVec = add_vec_vec(vec, vec);

    float ResAddVec[] = {2, 4, 2};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResAddVec[i] != ResVec->values[i][0])
            IsEqual = false;
    }
    matrix_destructor(ResVec);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::add_vec_vec_EmptyVector_ExpectError() {
    float ResAddVec[] = {2, 4, 2};

    matrix_t *ResVec = add_vec_vec(vec, vecEmpty);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResAddVec[i] != ResVec->values[0][i])
            IsEqual = false;
    }
    matrix_destructor(ResVec);
    CPPUNIT_ASSERT_EQUAL(false, IsEqual);
}

void MatrixTest::sub_vec_Vec_ValidVectors_ExpectCorrect() {
    float ResSubVec[] = {0, 0, 0};

    matrix_t *ResVec = sub_vec_vec(vec, vec);
    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        if (ResSubVec[i] != ResVec->values[0][i])
            IsEqual = false;
    }
    matrix_destructor(ResVec);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::sub_vec_vec_EmptyVectors_ExpectError() {
    float ResSubVec[] = {0, 0, 0};
    matrix_t *ResVec = sub_vec_vec(vec, vecEmpty);

    CPPUNIT_ASSERT_MESSAGE("sub_vec_vec allocated a vector eventhough a parameter was NULL.", ResVec == NULL);
}

void MatrixTest::inv_mat_ValidMatrix_ExpectCorrect() {
    float InvMat[3][3] = {{1, 2, 3},
                         {0, 1, 4},
                         {5, 6, 0}};

    matrix_t *matToInv = matrix_constructor(3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matToInv->values[i][j] = InvMat[i][j];
        }
    }

    matrix_t *resMat = inv_mat(matToInv);
    float ResMat[3][3] = {{-24, 18,  5},
                           {20,  -15, -4},
                           {-5,  4,   1}};

    bool IsEqual = true;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (ResMat[i][j] != resMat->values[i][j])
                IsEqual = false;
        }
    }
    matrix_destructor(matToInv);
    matrix_destructor(resMat);
    CPPUNIT_ASSERT_EQUAL(true, IsEqual);
}

void MatrixTest::inv_mat_InvalidMatrix_ExpectError() {
    float ResMat[3][3] = {  {-24, 18,  5},
                            {20,  -15, -4},
                            {-5,  4,   1}};

    matrix_t *matToInv = matrix_constructor(3, 3);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matToInv->values[i][j] = ResMat[i][j];
        }
    }

    matrix_t *res = inv_mat(matToInv);
    CPPUNIT_ASSERT(NULL == res);
}
