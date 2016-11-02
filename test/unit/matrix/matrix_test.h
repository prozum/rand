#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

class MatrixTest : public CppUnit::TestCase {
private:
    static CppUnit::TestSuite *multTests();
    static CppUnit::TestSuite *transTests();
    static CppUnit::TestSuite *addTests();
    static CppUnit::TestSuite *subTests();
    static CppUnit::TestSuite *invTests();

public:
    static CppUnit::TestSuite *suite();

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

};