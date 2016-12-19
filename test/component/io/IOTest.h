#pragma once

#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestFixture.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

extern "C" {
#include "avr_mcu_section.h"
#include "Tools.h"
}

#define ATMEGA328p "atmega328p"
#define F_CPU 16000000
#define STEPS 100000
#define INVALID_DDR "INVALID DDRx"
#define INVALID_PORT "INVALID PORTx"
#define INVALID_PIN "INVALID PINx"
#define WRONG_REG "CHANGED WRONG REGISTER"
#define INPUT 0
#define OUTPUT 1
#define LOW 0
#define HIGH 1

class IOTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(IOTest);

    CPPUNIT_TEST(SetPinMode_Pin0AndPin7SetOUT_ExpectBothOUT);

    CPPUNIT_TEST_SUITE_END();

  public:
    void SetPinMode_Pin0AndPin7SetOUT_ExpectBothOUT();
};