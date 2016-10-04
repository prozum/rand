#include <stdint.h>

#ifndef RAND_LOG_H
#define RAND_LOG_H

#define MAJOR_VERSION "0.0\0"
#define PROJECT_NAME "RAND(IE)\0"

typedef enum log_level {LOG_ONLY_ERRORS = 0, LOG_DEBUG = 1, LOG_ALL = 2, LOG_NONE = -1} level;

#endif //RAND_LOG_H

void toggle_logging(level lvl);
void LOG(char *msg);
void LOG_WARNING(char *msg);
void LOG_ERROR(char *msg);