#include <cppunit/ui/text/TestRunner.h>

#include "io/io_test.h"

int main(int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;

    CppUnit::Test *suite = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    runner.addTest(suite);

    runner.setOutputter( new CppUnit::CompilerOutputter( &runner.result(),
                                                         std::cerr ) );

    bool wasSucessful = runner.run();
    return wasSucessful ? 0 : 1;
}