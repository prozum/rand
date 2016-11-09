#include "log_test.h"

#include <string>
#include <malloc.h>
#include <stdint.h>

extern "C" {
#include "core/log.h"
#include "core/io.h"
}


using namespace std;
CPPUNIT_TEST_SUITE_REGISTRATION(LogTest);

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
    disable_device(SENDER_BOARD);

    LOG(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogWarningFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    clear_write_buffer(USB_TX);

    toggle_logging(LOG_ALL);
    disable_device(SENDER_BOARD);

    LOG_WARNING(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogErrorFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_device(SENDER_BOARD);

    LOG_ERROR(SENDER_BOARD, msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void LogTest::DisableDevice_LogErrorBypassFromDisabled_ExpectError(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_device(SENDER_BOARD);

    LOG_ERROR_BYPASS(msg);
    char *wb = get_write_buffer(USB_TX);

    CPPUNIT_ASSERT_MESSAGE("The message was not delivered against expectation.", wb != NULL);
}

void LogTest::DisableDevice_DisableSameTwice_ExpectOneOnList(){
    toggle_logging(LOG_ALL);
    disable_device(SENDER_BOARD);
    disable_device(SENDER_BOARD);

    uint8_t dev_count = count_disabled_devices();

    //Assert dev_count == 1
    CPPUNIT_ASSERT_MESSAGE("The same device is present in list twice.", 1 == dev_count);
}

void LogTest::SenderIgnored_OnIgnoredList_ExpectOne(){
    toggle_logging(LOG_ALL);
    disable_device(SENDER_BOARD);

    int blocked = sender_ignored(SENDER_BOARD);

    //Assert blocked == 1
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The SENDER_BOARD device has not been blocked properly.", 1, blocked);
}
void LogTest::SenderIgnored_NotOnList_ExpectZero(){
    toggle_logging(LOG_ALL);
    disable_device(SENDER_FC);
    disable_device(SENDER_IO);
    disable_device(SENDER_IR);
    disable_device(SENDER_LASER);
    disable_device(SENDER_SONAR);

    int blocked = sender_ignored(SENDER_BOARD);

    //Assert blocked == 0
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The SENDER_BOARD device was registered as blocked.", 0, blocked);
}