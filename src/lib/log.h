#include <stddef.h>

#ifndef RAND_LOG_H
#define RAND_LOG_H

#endif //RAND_LOG_H

#define MAJOR_VERSION "0.0\0"
#define PROJECT_NAME "RAND(IE)\0"
//Prefix defines:
static const char* WARNING_PREFIX = "W: ";
static const char* ERROR_PREFIX = "E: ";
static const char* MSG_PREFIX = "M: ";

typedef enum log_level_e {LOG_ONLY_ERRORS = 0, LOG_DEBUG = 1, LOG_ALL = 2, LOG_NONE = -1} level;
typedef enum log_sender_e {SENDER_SONAR, SENDER_IR, SENDER_IO, SENDER_LASER, SENDER_FC} log_sender;

typedef struct disabled_device_node {
    log_sender blocked_device;
    struct disabled_device *next;
} disabled_device;

//Head for the list of disable devices
static disabled_device *head = NULL;
//logging_level defines which class(es) of errors that should be logged
static level logging_level = LOG_NONE;

void toggle_logging(level lvl);
void LOG(log_sender sender, char *msg);
void LOG_WARNING(log_sender sender, char *msg);
void LOG_ERROR(log_sender, char *msg);
void LOG_ERROR_BYPASS(char *msg);
void disable_logging_for(log_sender device);