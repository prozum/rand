#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

#include "tools.h"

#define ATMEGA328p "atmega328p"
#define F_CPU 16000000
#define STEPS 1000
#define INVALID_DDR "INVALID DDRx"
#define INVALID_PORT "INVALID PORTx"
#define INVALID_PIN "INVALID PINx"
#define WRONG_REG "CHANGED WRONG REGISTER"

class IOTest : public CppUnit::TestCase {
public:
    void SetPinMode_Pin0SetIN_ExpectIN();
    void SetPinMode_Pin1SetIN_ExpectIN();
    void SetPinMode_Pin2SetIN_ExpectIN();
    void SetPinMode_Pin3SetIN_ExpectIN();
    void SetPinMode_Pin4SetIN_ExpectIN();
    void SetPinMode_Pin5SetIN_ExpectIN();
    void SetPinMode_Pin6SetIN_ExpectIN();
    void SetPinMode_Pin7SetIN_ExpectIN();
    void SetPinMode_Pin8SetIN_ExpectIN();
    void SetPinMode_Pin9SetIN_ExpectIN();
    void SetPinMode_Pin10SetIN_ExpectIN();
    void SetPinMode_Pin11SetIN_ExpectIN();
    void SetPinMode_Pin12SetIN_ExpectIN();
    void SetPinMode_Pin13SetIN_ExpectIN();

    void SetPinMode_Pin0SetOUT_ExpectOUT();
    void SetPinMode_Pin1SetOUT_ExpectOUT();
    void SetPinMode_Pin2SetOUT_ExpectOUT();
    void SetPinMode_Pin3SetOUT_ExpectOUT();
    void SetPinMode_Pin4SetOUT_ExpectOUT();
    void SetPinMode_Pin5SetOUT_ExpectOUT();
    void SetPinMode_Pin6SetOUT_ExpectOUT();
    void SetPinMode_Pin7SetOUT_ExpectOUT();
    void SetPinMode_Pin8SetOUT_ExpectOUT();
    void SetPinMode_Pin9SetOUT_ExpectOUT();
    void SetPinMode_Pin10SetOUT_ExpectOUT();
    void SetPinMode_Pin11SetOUT_ExpectOUT();
    void SetPinMode_Pin12SetOUT_ExpectOUT();
    void SetPinMode_Pin13SetOUT_ExpectOUT();

    void WritePin_Pin0WriteLOW_ExpectLOW();
    void WritePin_Pin1WriteLOW_ExpectLOW();
    void WritePin_Pin2WriteLOW_ExpectLOW();
    void WritePin_Pin3WriteLOW_ExpectLOW();
    void WritePin_Pin4WriteLOW_ExpectLOW();
    void WritePin_Pin5WriteLOW_ExpectLOW();
    void WritePin_Pin6WriteLOW_ExpectLOW();
    void WritePin_Pin7WriteLOW_ExpectLOW();
    void WritePin_Pin8WriteLOW_ExpectLOW();
    void WritePin_Pin9WriteLOW_ExpectLOW();
    void WritePin_Pin10WriteLOW_ExpectLOW();
    void WritePin_Pin11WriteLOW_ExpectLOW();
    void WritePin_Pin12WriteLOW_ExpectLOW();
    void WritePin_Pin13WriteLOW_ExpectLOW();

    void WritePin_Pin0WriteHIGH_ExpectHIGH();
    void WritePin_Pin1WriteHIGH_ExpectHIGH();
    void WritePin_Pin2WriteHIGH_ExpectHIGH();
    void WritePin_Pin3WriteHIGH_ExpectHIGH();
    void WritePin_Pin4WriteHIGH_ExpectHIGH();
    void WritePin_Pin5WriteHIGH_ExpectHIGH();
    void WritePin_Pin6WriteHIGH_ExpectHIGH();
    void WritePin_Pin7WriteHIGH_ExpectHIGH();
    void WritePin_Pin8WriteHIGH_ExpectHIGH();
    void WritePin_Pin9WriteHIGH_ExpectHIGH();
    void WritePin_Pin10WriteHIGH_ExpectHIGH();
    void WritePin_Pin11WriteHIGH_ExpectHIGH();
    void WritePin_Pin12WriteHIGH_ExpectHIGH();
    void WritePin_Pin13WriteHIGH_ExpectHIGH();
};