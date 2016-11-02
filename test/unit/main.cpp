#include <cppunit/ui/text/TestRunner.h>

#include "io/io_test.h"
#include "kalman/kalman_test.h"
#include "log/log_test.h"
#include "matrix/matrix_test.h"
#include "sonar/sonar_test.h"

int main(int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;

    runner.addTest(SonarTest::suite());
    runner.addTest(IOTest::suite());
    runner.addTest(KalmanTest::suite());
    runner.addTest(LogTest::suite());
    runner.addTest(MatrixTest::suite());

    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                         std::cerr ) );

    bool wasSucessful = runner.run();
    return wasSucessful ? 0 : 1;
}