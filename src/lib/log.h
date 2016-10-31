#include <stddef.h>
#include <stdint.h>

#ifndef RAND_LOG_H
#define RAND_LOG_H

#define MAJOR_VERSION "0.0\0"
#define PROJECT_NAME "RAND(IE)\0"

typedef enum log_level_e {LOG_ONLY_ERRORS = 0, LOG_DEBUG = 1, LOG_ALL = 2, LOG_NONE = -1} level;
typedef enum log_sender_e {SENDER_SONAR, SENDER_IR, SENDER_IO, SENDER_LASER, SENDER_FC, SENDER_BOARD} log_sender;

void toggle_logging(level lvl);
void LOG(log_sender sender, const char *msg);
void LOG_WARNING(log_sender sender, const char *msg);
void LOG_ERROR(log_sender, const char *msg);
void LOG_ERROR_BYPASS(const char *msg);
uint8_t sender_ignored(log_sender sender);
void disable_logging_for(log_sender device);

#if MOCK
uint8_t count_disabled_devices();
#endif //MOCK

#endif //RAND_LOG_H