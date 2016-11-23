#include <cppunit/ui/text/TestRunner.h>

#include "io/io_test.h"
#include "kalman/kalman_test.h"
#include "matrix/matrix_test.h"
#include "sonar/sonar_test.h"

int main(int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;
    CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
    runner.addTest(registry.makeTest());

    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                         std::cerr ) );

    bool wasSucessful = runner.run();
    return wasSucessful ? 0 : 1;
}