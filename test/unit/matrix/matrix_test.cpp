#include "matrix_test.h"

CPPUNIT_TEST_SUITE_REGISTRATION(MatrixTest);

void MatrixTest::setUp_mat1() {
    float mat[3][3] = {{9.1, 6.0, 2.8},
                        {7.4, 1.0, 3.0},
                        {4.5, 0.0, 8.0}};
    for (int i = 0; i < ma1->rows; ++i) {
        for (int j = 0; j < ma1->columns; ++j) {
            matrix_set(ma1, i, j, mat[i][j]);
        }
    }
}

void MatrixTest::setup_mat2() {
    float mat[3][3] = {{1.0, 2.0, 3.0},
                        {4.0, 5.0, 6.0},
                        {7.0, 8.0, 9.0}};
    for (int i = 0; i < ma2->rows; ++i) {
        for (int j = 0; j < ma2->columns; ++j) {
            matrix_set(ma2, i, j, mat[i][j]);
        }
    }
}

void MatrixTest::setup_mat3() {
    float mat[2][2] = {{32.1, 8.3},
                        {0.72, 43.7}};
    for (int i = 0; i < ma3->rows; ++i) {
        for (int j = 0; j < ma3->columns; ++j) {
            matrix_set(ma3, i, j, mat[i][j]);
        }
    }

}

void MatrixTest::setup_mat4() {
    float mat[3][2] = {{1, 2},
                        {3, 4},
                        {5, 6}};

    for (int i = 0; i < ma4->rows; ++i) {
        for (int j = 0; j < ma4->columns; ++j) {
            matrix_set(ma4, i, j, mat[i][j]);
        }
    }
}

void MatrixTest::setup_vec() {
    float ve[3][1] = {{1} , {2}, {1}};

    for (int i = 0; i < vec->rows; ++i) {
        matrix_set (vec, i, 0, ve[i][0]);
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
    matrix_destructor(ma1);
    matrix_destructor(ma2);
    matrix_destructor(ma3);
    matrix_destructor(ma4);
    matrix_destructor(vec);
}

void MatrixTest::mult_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat = mult_mat_mat(ma1, ma2);
    float ResMulMat3x3[3][3] = {{52.7, 70.6, 88.5},
                                 {32.4, 43.8, 55.2},
                                 {60.5, 73.0, 85.5}};

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect matrix-rows", resMat->rows, ma1->rows);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect matrix-columns", resMat->columns, ma2->columns);

    for (int i = 0; i < resMat->rows; ++i) {
        for (int j = 0; j < resMat->columns; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResMulMat3x3[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::mult_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = mult_mat_mat(ma1, ma3);
    CPPUNIT_ASSERT(resMat == NULL);
    //resMat is NULL due to invalid multiplication -- no need to destroy
}

void MatrixTest::mult_mat_mat_DifferentSizes_ExpectCorrect() {
    matrix_t *resMat;
    resMat = mult_mat_mat(ma1, ma4);
    float ResMulMat[3][2] = {{41.1, 59},
                             {25.4, 36.8},
                             {44.5, 57}};

    CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect matrix-rows", resMat->rows, ma1->rows);
    CPPUNIT_ASSERT_EQUAL_MESSAGE("Incorrect matrix-columns", resMat->columns, ma4->columns);

    for (int i = 0; i < resMat->rows; ++i) {
        for (int j = 0; j < resMat->columns; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResMulMat[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::trans_matrix_SquareMatrix_ExpectTransposed() {
    float ResTransMat[3][3] = {{1, 4, 7},
                                {2, 5, 8},
                                {3, 6, 9}};
    matrix_t *resMat = trans_matrix(ma2);

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResTransMat[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::trans_matrix_NotSquareMatrix_ExpectTransposed() {
    float ResTransMat[2][3] = {{1, 3, 5},
                                {2, 4, 6}};
    matrix_t *resMat = trans_matrix(ma4);

    for (int i = 0; i < resMat->rows; ++i) {
        for (int j = 0; j < resMat->columns; ++j) {
            std::string msg = "At index " + std::to_string(i) + ", " + std::to_string(j);
            CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, ResTransMat[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::add_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat = add_mat_mat(ma1, ma2);
    float ResAddMat3x3[3][3] = {{10.1, 8, 5.8},
                                 {11.4, 6, 9},
                                 {11.5, 8, 17}};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResAddMat3x3[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::add_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = add_mat_mat(ma1, ma3);
    CPPUNIT_ASSERT(resMat == NULL);
    //resMat is NULL due to incompatible sizes -- no need to destroy
}

void MatrixTest::sub_mat_mat_ValidMatrix_ExpectCorrect() {
    matrix_t *resMat;
    resMat = sub_mat_mat(ma1, ma2);
    float ResSubMat3x3[3][3] = {{8.1,  4,  -0.2},
                                 {3.4,  -4, -3},
                                 {-2.5, -8, -1}};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResSubMat3x3[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::sub_mat_mat_InvalidMatrix_ExpectError() {
    matrix_t *resMat = sub_mat_mat(ma1, ma3);
    CPPUNIT_ASSERT(resMat == NULL);
    //resMat is NULL due to invalid matrix sizes -- no need to destroy
}

void MatrixTest::ident_mat_ExpectCorrect() {
    matrix_t *resMat = ident_mat(3);
    float ResIdentMat3[3][3] = {{1, 0, 0},
                                 {0, 1, 0},
                                 {0, 0, 1}};

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::string msg = "At index " + std::to_string(i) + ", " + std::to_string(j);
            CPPUNIT_ASSERT_EQUAL_MESSAGE(msg, ResIdentMat3[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(resMat);
}

void MatrixTest::add_vec_vec_ValidVectors_ExpectCorrect() {
    matrix_t *ResVec = add_vec_vec(vec, vec);

    float ResAddVec[] = {2, 4, 2};

    for (int i = 0; i < 3; ++i) {
        CPPUNIT_ASSERT_EQUAL(ResAddVec[i], matrix_get(ResVec, i, 0));
    }
    matrix_destructor(ResVec);
}

void MatrixTest::add_vec_vec_EmptyVector_ExpectError() {
    matrix_t *ResVec = add_vec_vec(vec, vecEmpty);
    CPPUNIT_ASSERT(ResVec == NULL);
}

void MatrixTest::sub_vec_Vec_ValidVectors_ExpectCorrect() {
    float ResSubVec[3] = {0, 0, 0};

    matrix_t *ResVec = sub_vec_vec(vec, vec);
    for (int i = 0; i < ResVec->columns; ++i) {
        CPPUNIT_ASSERT_EQUAL(ResSubVec[i], matrix_get(ResVec, i, 0));
    }
    matrix_destructor(ResVec);
}

void MatrixTest::sub_vec_vec_EmptyVectors_ExpectError() {
    matrix_t *ResVec = sub_vec_vec(vec, vecEmpty);

    CPPUNIT_ASSERT_MESSAGE("sub_vec_vec allocated a vector eventhough a parameter was NULL.", ResVec == NULL);
}

void MatrixTest::inv_mat_ValidMatrix_ExpectCorrect() {
    float InvMat[2][2] = {{1, 2},
                          {4, 6}};

    matrix_t *matToInv = matrix_constructor(2, 2);

    for (int i = 0; i < matToInv->rows; ++i) {
        for (int j = 0; j < matToInv->columns; ++j) {
            matrix_set(matToInv, i, j, InvMat[i][j]);
        }
    }

    matrix_t *resMat = inv_mat(matToInv);
    float ResMat[2][2] = {{-3, 1},
                          {2, -0.5}};

    for (int i = 0; i < matToInv->rows; ++i) {
        for (int j = 0; j < matToInv->columns; ++j) {
            CPPUNIT_ASSERT_EQUAL(ResMat[i][j], matrix_get(resMat, i, j));
        }
    }
    matrix_destructor(matToInv);
    matrix_destructor(resMat);
}

void MatrixTest::inv_mat_InvalidMatrix_ExpectError() {
    float ResMat[3][3] = {  {-24, 18,  5},
                            {20,  -15, -4},
                            {-5,  4,   1}};

    //Allocate and fill a matrix with the matrix_t type instead of float[][]
    matrix_t *matToInv = matrix_constructor(3, 3);
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            matrix_set(matToInv, i, j, ResMat[i][j]);
        }
    }

    matrix_t *res = inv_mat(matToInv);
    CPPUNIT_ASSERT(NULL == res);
}

void MatrixTest::matrix_get_1x1_ExpectCorrect() {
    float value[1][1] = {{10}};

    matrix_t *get_from = matrix_constructor(1, 1);
    get_from->values[0] = value[0][0];

    CPPUNIT_ASSERT_EQUAL(value[0][0], matrix_get(get_from, 0, 0));
    matrix_destructor(get_from);
}
void MatrixTest::matrix_get_1x2_ExpectCorrect() {
    float vector[1][2] = {{2, 4}};

    matrix_t *get_from = matrix_constructor(1, 2);
    get_from->values[0] = vector[0][0];
    get_from->values[1] = vector[0][1];

    CPPUNIT_ASSERT_EQUAL(vector[0][0], matrix_get(get_from, 0, 0));
    CPPUNIT_ASSERT_EQUAL(vector[0][1], matrix_get(get_from, 0, 1));
    matrix_destructor(get_from);
}
void MatrixTest::matrix_get_2x1_ExpectCorrect() {
    float vector[2][1] = {{2},
                          {4}};

    matrix_t *get_from = matrix_constructor(2, 1);
    get_from->values[0] = vector[0][0];
    get_from->values[1] = vector[1][0];

    CPPUNIT_ASSERT_EQUAL(vector[0][0], matrix_get(get_from, 0, 0));
    CPPUNIT_ASSERT_EQUAL(vector[1][0], matrix_get(get_from, 1, 0));
    matrix_destructor(get_from);
}
void MatrixTest::matrix_get_2x2_ExpectCorrect() {
    float matrix[2][2] = {{2, 6},
                          {4, 12}};

    matrix_t *get_from = matrix_constructor(2, 2);
    uint8_t mat_index = 0;
    for(int i = 0; i < get_from->rows; i++) {
        for(int j = 0; j < get_from->columns; j++) {
            get_from->values[mat_index] = matrix[i][j];
            mat_index++;
        }
    }

    for(int i = 0; i < get_from->rows; i++) {
        for(int j = 0; j < get_from->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(matrix[i][j], matrix_get(get_from, i, j));
        }
    }
    matrix_destructor(get_from);
}
void MatrixTest::matrix_get_3x3_ExpectCorrect() {
    float matrix[3][3] = {{2, 6, 8},
                          {4, 12, 18},
                          {8, 18, 24}};
    matrix_t *get_from = matrix_constructor(3, 3);

    uint8_t mat_index = 0;
    for(int i = 0; i < get_from->rows; i++) {
        for(int j = 0; j < get_from->columns; j++) {
            get_from->values[mat_index] = matrix[i][j];
            mat_index++;
        }
    }

    for(int i = 0; i < get_from->rows; i++) {
        for(int j = 0; j < get_from->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(matrix[i][j], matrix_get(get_from, i, j));
        }
    }
    matrix_destructor(get_from);
}

void MatrixTest::matrix_set_1x1_ExpectCorrect() {
    float value[1][1] = {{10}};

    matrix_t *set_to = matrix_constructor(1, 1);

    matrix_set(set_to, 0, 0, value[0][0]);

    CPPUNIT_ASSERT_EQUAL(value[0][0], set_to->values[0]);
    matrix_destructor(set_to);
}

void MatrixTest::matrix_set_1x2_ExpectCorrect() {
    float vector[1][2] = {{2, 4}};

    matrix_t *set_to = matrix_constructor(1, 2);

    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            matrix_set(set_to, i, j, vector[i][j]);
        }
    }

    uint8_t mat_index = 0;
    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(vector[i][j], set_to->values[mat_index]);
            mat_index++;
        }
    }
    matrix_destructor(set_to);
}
void MatrixTest::matrix_set_2x1_ExpectCorrect() {
    float vector[2][1] = {{2},
                          {4}};

    matrix_t *set_to = matrix_constructor(1, 2);

    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            matrix_set(set_to, i, j, vector[i][j]);
        }
    }

    uint8_t mat_index = 0;
    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(vector[i][j], set_to->values[mat_index]);
            mat_index++;
        }
    }
    matrix_destructor(set_to);
}
void MatrixTest::matrix_set_2x2_ExpectCorrect() {
    float matrix[2][2] = {{2, 6},
                          {4, 12}};

    matrix_t *set_to = matrix_constructor(1, 2);

    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            matrix_set(set_to, i, j, matrix[i][j]);
        }
    }

    uint8_t mat_index = 0;
    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(matrix[i][j], set_to->values[mat_index]);
            mat_index++;
        }
    }
    matrix_destructor(set_to);
}
void MatrixTest::matrix_set_3x3_ExpectCorrect() {
    float matrix[3][3] = {{2, 6, 8},
                          {4, 12, 18},
                          {8, 18, 24}};

    matrix_t *set_to = matrix_constructor(1, 2);

    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            matrix_set(set_to, i, j, matrix[i][j]);
        }
    }

    uint8_t mat_index = 0;
    for(int i = 0; i < set_to->rows; i++) {
        for(int j = 0; j < set_to->columns; j++) {
            CPPUNIT_ASSERT_EQUAL(matrix[i][j], set_to->values[mat_index]);
            mat_index++;
        }
    }
    matrix_destructor(set_to);
}
