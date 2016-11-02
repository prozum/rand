#pragma once

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/TestRunner.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestResult.h>

class LogTest : public CppUnit::TestCase {
private:
    static CppUnit::TestSuite *toggleLoggingTests();
    static CppUnit::TestSuite *logTests();
    static CppUnit::TestSuite *disableDeviceTests();
    static CppUnit::TestSuite *senderIgnoredTests();

    public :
    static CppUnit::TestSuite *suite();

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
