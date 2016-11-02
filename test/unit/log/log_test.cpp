#include <malloc.h>
#include "log_test.h"
#include "log/log.h"
#include "io/io.h"
#include <string>
#include <stdint.h>

using namespace std;
using namespace CppUnit;

static TestSuite *LogTest::suite() {
    TestSuite *suite = new TestSuite("LogTest");
    suite->addTest(LogTest::disableDeviceTests());
    suite->addTest(LogTest::senderIgnoredTests());
    suite->addTest(LogTest::logTests());
    suite->addTest(LogTest::toggleLoggingTests());
}

static TestSuite *LogTest::disableDeviceTests() {
    TestSuite *ddSuite = new TestSuite("DisableDevice");

    ddSuite->addTest(new TestCaller(
            "_LogFromDisabled_ExpectNothing", &LogTest::DisableDevice_LogFromDisabled_ExpectNothing
    ));
    ddSuite->addTest(new TestCaller(
            "_LogWarningFromDisabled_ExpectNothing", &LogTest::DisableDevice_LogWarningFromDisabled_ExpectNothing
    ));
    ddSuite->addTest(new TestCaller(
            "_LogErrorFromDisabled_ExpectNothing", &LogTest::DisableDevice_LogErrorFromDisabled_ExpectNothing
    ));
    ddSuite->addTest(new TestCaller(
            "_LogErrorBypassFromDisabled_ExpectError", &LogTest::DisableDevice_LogErrorBypassFromDisabled_ExpectError
    ));
    ddSuite->addTest(new TestCaller(
            "_DisableSameTwice_ExpectOneOnList", &LogTest::DisableDevice_DisableSameTwice_ExpectOneOnList
    ));

    return ddSuite;
}

static TestSuite *LogTest::senderIgnoredTests() {
    TestSuite *siSuite = new TestSuite("SenderIgnored");

    siSuite->addTest(new TestCaller(
            "_NotOnList_ExpectZero", &LogTest::SenderIgnored_NotOnList_ExpectZero
    ));
    siSuite->addTest(new TestCaller(
            "_OnIgnoredList_ExpectOne", &LogTest::SenderIgnored_OnIgnoredList_ExpectOne
    ));

    return siSuite;
}

static TestSuite *LogTest::logTests() {
    TestSuite *lSuite = new TestSuite("Log");

    lSuite->addTest(new TestCaller(
            "_Testlog_ExpectMsgTestlog", &LogTest::Log_Testlog_ExpectMsgTestlog
    ));
    lSuite->addTest(new TestCaller(
            "Warning_Testlog_ExpectWarTestLog", &LogTest::LogWarning_Testlog_ExpectWarTestlog
    ));
    lSuite->addTest(new TestCaller(
            "Error_Testlog_ExpectErrTestlog", &LogTest::LogError_Testlog_ExpectErrTestlog
    ));
    lSuite->addTest(new TestCaller(
            "ErrorBypass_Testlog_ExpectErrTestlog", &LogTest::LogErrorBypass_Testlog_ExpectErrTestLog
    ));

    return lSuite;
}

static TestSuite *LogTest::toggleLoggingTests() {
    TestSuite *tlSuite = new TestSuite("ToggleLogging");

    tlSuite->addTest(new TestCaller(
            "_ShowAllMessages_ExpectMessage", &LogTest::ToggleLogging_ShowAllMessages_ExpectMessage
    ));
    tlSuite->addTest(new TestCaller(
            "_ShowWarnings_ExpectErrorsAndWarningAndNoMessages",
            &LogTest::ToggleLogging_ShowWarnings_ExpectErrorsAndWarningsAndNoMessages
    ));
    tlSuite->addTest(new TestCaller(
            "_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings",
            &LogTest::ToggleLogging_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings
    ));
    tlSuite->addTest(new TestCaller(
            "_ShowNone_ExpectBypass", &LogTest::ToggleLogging_ShowNone_ExpectBypass
    ));

    return tlSuite;
}

void LogTest::ToggleLogging_ShowAllMessages_ExpectMessage(){
    char *wb;
    toggle_logging(LOG_ALL);

    clear_write_buffer(USB_TX);
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The message was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The warning was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void LogTest::ToggleLogging_ShowWarnings_ExpectErrorsAndWarningsAndNoMessages() {
    char *wb;
    toggle_logging(LOG_DEBUG);

    clear_write_buffer(USB_TX);
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);

    clear_write_buffer(USB_TX);
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The warning was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void LogTest::ToggleLogging_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings() {
    char *wb;
    toggle_logging(LOG_ONLY_ERRORS);

    clear_write_buffer(USB_TX);
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The warning was delivered against expectation.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void LogTest::ToggleLogging_ShowNone_ExpectBypass() {
    char *wb;
    toggle_logging(LOG_NONE);

    clear_write_buffer(USB_TX);
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The warning was delivered against expectation.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The error was delivered against expectation.", wb != NULL);

    clear_write_buffer(USB_TX);
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer(USB_TX);
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was delivered against expectation.", wb != NULL);
}

void LogTest::Log_Testlog_ExpectMsgTestlog() {
    char const *msg = "Testlog";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "M: ";
    assrt += msg;

    char *wb = get_write_buffer(USB_TX);

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogTest::LogWarning_Testlog_ExpectWarTestlog() {
    char const *msg = "Testlog";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "W: ";
    assrt += msg;

    char *wb = get_write_buffer(USB_TX);

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogTest::LogError_Testlog_ExpectErrTestlog() {
    char const *msg = "Testlog";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "E: ";
    assrt += msg;

    char *wb = get_write_buffer(USB_TX);

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogTest::LogErrorBypass_Testlog_ExpectErrTestLog() {
    char const *msg = "Testlog";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "E: ";
    assrt += msg;

    char *wb = get_write_buffer(USB_TX);

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}

void LogTest::DisableDevice_LogFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogWarningFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_WARNING(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogErrorFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_ERROR(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogErrorBypassFromDisabled_ExpectError(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_ERROR_BYPASS(msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was not delivered against expectation.", wb != NULL);
}

void LogTest::DisableDevice_DisableSameTwice_ExpectOneOnList(){
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);
    disable_logging_for(SENDER_BOARD);

    uint8_t dev_count = count_disabled_devices();

    //Assert dev_count == 1
    CPPUNIT_ASSERT_MESSAGE("The same device is present in list twice.", 1 == dev_count);
}

void LogTest::SenderIgnored_OnIgnoredList_ExpectOne(){
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    int blocked = sender_ignored(SENDER_BOARD);

    //Assert blocked == 1
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The SENDER_BOARD device has not been blocked properly.", 1, blocked);
}
void LogTest::SenderIgnored_NotOnList_ExpectZero(){
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_FC);
    disable_logging_for(SENDER_IO);
    disable_logging_for(SENDER_IR);
    disable_logging_for(SENDER_LASER);
    disable_logging_for(SENDER_SONAR);

    int blocked = sender_ignored(SENDER_BOARD);

    //Assert blocked == 0
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The SENDER_BOARD device was registered as blocked.", 0, blocked);
}