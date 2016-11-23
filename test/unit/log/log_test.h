#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

extern "C" {
#include "core/log.h"
#include "core/io.h"
}

class LogTest : public CppUnit::TestCase {
        CPPUNIT_TEST_SUITE(LogTest);
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

        CPPUNIT_TEST(SenderIgnored_OnIgnoredList_ExpectOne);
        CPPUNIT_TEST(SenderIgnored_NotOnList_ExpectZero);
        CPPUNIT_TEST_SUITE_END();

public :

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

    void SenderIgnored_OnIgnoredList_ExpectOne();

    void SenderIgnored_NotOnList_ExpectZero();
};
