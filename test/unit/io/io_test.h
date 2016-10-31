#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

#include "tools.h"
#include "avr_mcu_section.h"

#define ATMEGA328p "atmega328p"
#define F_CPU 16000000
#define STEPS 1000
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
    CPPUNIT_TEST_SUITE_END();

public:
    void SetPinMode_Pin0SetIN_ExpectIN();
    void SetPinMode_Pin7SetIN_ExpectIN();
    void SetPinMode_Pin8SetIN_ExpectIN();
    void SetPinMode_Pin13SetIN_ExpectIN();
    void SetPinMode_Pin0SetOUT_ExpectOUT();
    void SetPinMode_Pin7SetOUT_ExpectOUT();
    void SetPinMode_Pin8SetOUT_ExpectOUT();
    void SetPinMode_Pin13SetOUT_ExpectOUT();
    void SetPinMode_Pin13SetHigherThan1_ExpectNoChange();

    void WritePin_Pin0WriteLOW_ExpectLOW();
    void WritePin_Pin7WriteLOW_ExpectLOW();
    void WritePin_Pin8WriteLOW_ExpectLOW();
    void WritePin_Pin13WriteLOW_ExpectLOW();
    void WritePin_Pin0WriteHIGH_ExpectHIGH();
    void WritePin_Pin7WriteHIGH_ExpectHIGH();
    void WritePin_Pin8WriteHIGH_ExpectHIGH();
    void WritePin_Pin13WriteHIGH_ExpectHIGH();
    void WritePin_Pin13WriteHigherThan1_ExpectNoChange();

    void ReadPin_Pin0ReadLOW_ExpectLOW();
    void ReadPin_Pin7ReadLOW_ExpectLOW();
    void ReadPin_Pin8ReadLOW_ExpectLOW();
    void ReadPin_Pin13ReadLOW_ExpectHIGH();
    void ReadPin_Pin0ReadHIGH_ExpectHIGH();
    void ReadPin_Pin7ReadHIGH_ExpectHIGH();
    void ReadPin_Pin8ReadHIGH_ExpectHIGH();
    void ReadPin_Pin13ReadHIGH_ExpectHIGH();
};