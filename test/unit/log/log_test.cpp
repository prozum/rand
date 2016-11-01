#include <malloc.h>
#include "log_test.h"
#include "log.h"
#include "io.h"
#include <string>

using namespace std;

void ToggleLogging_LogAll_ExpectMessage(){
    char *wb;
    toggle_logging(LOG_ALL);

    clear_write_buffer();
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The message was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The warning was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void ToggleLogging_ShowWarnings_ExpectErrorsAndWarningsAndNoMessages(){
    char *wb;
    toggle_logging(LOG_DEBUG);

    clear_write_buffer();
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);

    clear_write_buffer();
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The warning was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void ToggleLogging_ShowErrors_ExpectErrorsAndNoMessagesAndWarnings(){
    char *wb;
    toggle_logging(LOG_ONLY_ERRORS);

    clear_write_buffer();
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb != NULL);

    clear_write_buffer();
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The warning was delivered against expectation.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The error was not delivered correctly.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was not delivered correctly.", wb != NULL);
}
void ToggleLogging_ShowNone_ExpectBypass(){
    char *wb;
    toggle_logging(LOG_NONE);

    clear_write_buffer();
    LOG(SENDER_BOARD, "Test message");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb != NULL);

    clear_write_buffer();
    LOG_WARNING(SENDER_BOARD, "Test warning");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The warning was delivered against expectation.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR(SENDER_BOARD, "Test error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The error was delivered against expectation.", wb != NULL);

    clear_write_buffer();
    LOG_ERROR_BYPASS("Test bypass error");
    wb = get_write_buffer();
    CPPUNIT_ASSERT_MESSAGE("The bypassed error was delivered against expectation.", wb != NULL);
}

void Log_Testlog_ExpectMsgTestlog(){
    char const *msg = "Testlog";
    clear_write_buffer();

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "M: ";
    assrt += msg;

    char *wb = get_write_buffer();

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogWarning_Testlog_ExpectWarTestlog(){
    char const *msg = "Testlog";
    clear_write_buffer();

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "W: ";
    assrt += msg;

    char *wb = get_write_buffer();

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogError_Testlog_ExpectErrTestlog(){
    char const *msg = "Testlog";
    clear_write_buffer();

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "E: ";
    assrt += msg;

    char *wb = get_write_buffer();

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}
void LogErrorBypass_Testlog_ExpectErrTestLog(){
    char const *msg = "Testlog";
    clear_write_buffer();

    toggle_logging(LOG_ALL);
    LOG(SENDER_BOARD, msg);

    string assrt = "E: ";
    assrt += msg;

    char *wb = get_write_buffer();

    string a_msg = "Expected the strings to be equal but found - e: ";
    a_msg += assrt;
    a_msg += " f: ";
    a_msg += wb;

    CPPUNIT_ASSERT_MESSAGE(a_msg, !assrt.compare(wb));
}

void DisableDevice_LogFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG(SENDER_BOARD, msg);
    char *wb = get_write_buffer();

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void DisableDevice_LogWarningFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    clear_write_buffer();

    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_WARNING(SENDER_BOARD, msg);
    char *wb = get_write_buffer();

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void DisableDevice_LogErrorFromDisabled_ExpectNothing(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_ERROR(SENDER_BOARD, msg);
    char *wb = get_write_buffer();

    CPPUNIT_ASSERT_MESSAGE("The message was delivered against expectation.", wb == NULL);
}
void DisableDevice_LogErrorBypassFromDisabled_ExpectError(){
    char const *msg = "Disabled Log";
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    LOG_ERROR_BYPASS(msg);
    char *wb = get_write_buffer();

    CPPUNIT_ASSERT_MESSAGE("The message was not delivered against expectation.", wb != NULL);
}

void DisableDevice_DisableSameTwice_ExpectOneOnList(){
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);
    disable_logging_for(SENDER_BOARD);

    uint8_t dev_count = count_disabled_devices();

    //Assert dev_count == 1
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The same device is present in list twice.", 1, dev_count);
}

void SenderIgnored_OnIgnoredList_ExpectOne(){
    toggle_logging(LOG_ALL);
    disable_logging_for(SENDER_BOARD);

    int blocked = sender_ignored(SENDER_BOARD);

    //Assert blocked == 1
    CPPUNIT_ASSERT_EQUAL_MESSAGE("The SENDER_BOARD device has not been blocked properly.", 1, blocked);
}
void SenderIgnored_NotOnList_ExpectZero(){
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