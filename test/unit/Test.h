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


class Test : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(Test);
/*
    // IO - Pinmode
    CPPUNIT_TEST(SetPinMode_Pin0SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin7SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin8SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin13SetIN_ExpectIN);
    CPPUNIT_TEST(SetPinMode_Pin0SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin7SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin8SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin13SetOUT_ExpectOUT);
    CPPUNIT_TEST(SetPinMode_Pin13SetHigherThan1_ExpectNoChange);

    // IO - WritePin
    CPPUNIT_TEST(WritePin_Pin0WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin7WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin8WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin13WriteLOW_ExpectLOW);
    CPPUNIT_TEST(WritePin_Pin0WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin7WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin8WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin13WriteHIGH_ExpectHIGH);
    CPPUNIT_TEST(WritePin_Pin13WriteHigherThan1_ExpectNoChange);

    // IO - ReadPin
    CPPUNIT_TEST(ReadPin_Pin0ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin7ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin8ReadLOW_ExpectLOW);
    CPPUNIT_TEST(ReadPin_Pin13ReadLOW_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin0ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin7ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin8ReadHIGH_ExpectHIGH);
    CPPUNIT_TEST(ReadPin_Pin13ReadHIGH_ExpectHIGH);

    // Kalman - Single
    CPPUNIT_TEST(SingleKalmanInit_NullAsStateValidParams_ExpectInvalidState );

    // Log
    CPPUNIT_TEST(ToggleLogging_ShowAllMessages_ExpectMessage);
    CPPUNIT_TEST(ToggleLogging_ShowWarnings_ExpectErrorsAndWarningsAndNoMessages);
    CPPUNIT_TEST(ToggleLogging_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings);
    CPPUNIT_TEST(ToggleLogging_ShowNone_ExpectBypass);

    CPPUNIT_TEST(Log_Testlog_ExpectMsgTestlog);
    CPPUNIT_TEST(LogWarning_Testlog_ExpectWarTestlog);
    CPPUNIT_TEST(LogError_Testlog_ExpectErrTestlog);
    CPPUNIT_TEST(LogErrorBypass_Testlog_ExpectErrTestLog);

    CPPUNIT_TEST(DisableDevice_LogFromDisabled_ExpectNothing);
    CPPUNIT_TEST(DisableDevice_LogWarningFromDisabled_ExpectNothing);
    CPPUNIT_TEST(DisableDevice_LogErrorFromDisabled_ExpectNothing);
    CPPUNIT_TEST(DisableDevice_LogErrorBypassFromDisabled_ExpectError);

    CPPUNIT_TEST(DisableDevice_DisableSameTwice_ExpectOneOnList);

    // Matrix
    CPPUNIT_TEST(SenderIgnored_OnIgnoredList_ExpectOne);
    CPPUNIT_TEST(SenderIgnored_NotOnList_ExpectZero);};
    CPPUNIT_TEST(mult_mat_mat_ValidMatrix_ExpectCorrect);
    CPPUNIT_TEST(mult_mat_mat_InvalidMatrix_ExpectError);
    CPPUNIT_TEST(mult_mat_mat_DifferentSizes_ExpectCorrect);
    CPPUNIT_TEST(trans_matrix_SquareMatrix_ExpectTransposed);
    CPPUNIT_TEST(trans_matrix_NotSquareMatrix_ExpectTransposed);
    CPPUNIT_TEST(add_mat_mat_ValidMatrix_ExpectCorrect);
    CPPUNIT_TEST(add_mat_mat_InvalidMatrix_ExpectError);
    CPPUNIT_TEST(sub_mat_mat_ValidMatrix_ExpectCorrect);
    CPPUNIT_TEST(sub_mat_mat_InvalidMatrix_ExpectError);
    CPPUNIT_TEST(ident_mat_ExpectCorrect);
    CPPUNIT_TEST(add_vec_vec_ValidVectors_ExpectCorrect);
    CPPUNIT_TEST(add_vec_vec_EmptyVector_ExpectError);
    CPPUNIT_TEST(sub_vec_Vec_ValidVectors_ExpectCorrect);
    CPPUNIT_TEST(sub_vec_vec_EmptyVectors_ExpectError);
    CPPUNIT_TEST(inv_mat_ValidMatrix_ExpectCorrect);
    CPPUNIT_TEST(inv_mat_InvalidMatrix_ExpectError);

    // Sonar
    CPPUNIT_TEST(sonarInit_expectTriggerOutAndEchoIn);
    CPPUNIT_TEST(pulseSonar_expectBuffer010);

    CPPUNIT_TEST(readSonar_inRange_expectRange110To22000);
    CPPUNIT_TEST(readSonar_outOfRange_expectValidByteZero);
    CPPUNIT_TEST(readSonar_tooClose_expectValidByteZero);

    CPPUNIT_TEST(sonarToMeters_110_expect2dot41);
    CPPUNIT_TEST(sonarToMeters_8000_expect158dot57);
    CPPUNIT_TEST(sonarToMeters_22000_expect453dot68);

    CPPUNIT_TEST_SUITE_END();
    */

 protected:
    // IO - Pinmode
    void SetPinMode_Pin0SetIN_ExpectIN();
    void SetPinMode_Pin7SetIN_ExpectIN();
    void SetPinMode_Pin8SetIN_ExpectIN();
    void SetPinMode_Pin13SetIN_ExpectIN();
    void SetPinMode_Pin0SetOUT_ExpectOUT();
    void SetPinMode_Pin7SetOUT_ExpectOUT();
    void SetPinMode_Pin8SetOUT_ExpectOUT();
    void SetPinMode_Pin13SetOUT_ExpectOUT();
    void SetPinMode_Pin13SetHigherThan1_ExpectNoChange();

    // IO - WritePin
    void WritePin_Pin0WriteLOW_ExpectLOW();
    void WritePin_Pin7WriteLOW_ExpectLOW();
    void WritePin_Pin8WriteLOW_ExpectLOW();
    void WritePin_Pin13WriteLOW_ExpectLOW();
    void WritePin_Pin0WriteHIGH_ExpectHIGH();
    void WritePin_Pin7WriteHIGH_ExpectHIGH();
    void WritePin_Pin8WriteHIGH_ExpectHIGH();
    void WritePin_Pin13WriteHIGH_ExpectHIGH();
    void WritePin_Pin13WriteHigherThan1_ExpectNoChange();

    // IO - ReadPin
    void ReadPin_Pin0ReadLOW_ExpectLOW();
    void ReadPin_Pin7ReadLOW_ExpectLOW();
    void ReadPin_Pin8ReadLOW_ExpectLOW();
    void ReadPin_Pin13ReadLOW_ExpectHIGH();
    void ReadPin_Pin0ReadHIGH_ExpectHIGH();
    void ReadPin_Pin7ReadHIGH_ExpectHIGH();
    void ReadPin_Pin8ReadHIGH_ExpectHIGH();
    void ReadPin_Pin13ReadHIGH_ExpectHIGH();

    // Kalman - Single
    void SingleKalmanInit_NullAsStateValidParams_ExpectInvalidState ();

    // Log
    void ToggleLogging_ShowAllMessages_ExpectMessage();
    void ToggleLogging_ShowWarnings_ExpectErrorsAndWarningsAndNoMessages();
    void ToggleLogging_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings();
    void ToggleLogging_ShowNone_ExpectBypass();

    void Log_Testlog_ExpectMsgTestlog();
    void LogWarning_Testlog_ExpectWarTestlog();
    void LogError_Testlog_ExpectErrTestlog();
    void LogErrorBypass_Testlog_ExpectErrTestLog();

    void DisableDevice_LogFromDisabled_ExpectNothing();
    void DisableDevice_LogWarningFromDisabled_ExpectNothing();
    void DisableDevice_LogErrorFromDisabled_ExpectNothing();
    void DisableDevice_LogErrorBypassFromDisabled_ExpectError();

    void DisableDevice_DisableSameTwice_ExpectOneOnList();

    // Matrix
    void SenderIgnored_OnIgnoredList_ExpectOne();
    void SenderIgnored_NotOnList_ExpectZero();
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

    // Sonar
    void sonarInit_expectTriggerOutAndEchoIn();
    void pulseSonar_expectBuffer010();

    void readSonar_inRange_expectRange110To22000();
    void readSonar_outOfRange_expectValidByteZero();
    void readSonar_tooClose_expectValidByteZero();

    void sonarToMeters_110_expect2dot41();
    void sonarToMeters_8000_expect158dot57();
    void sonarToMeters_22000_expect453dot68();
}

CPPUNIT_TEST_SUITE_REGISTRATION( Test );
