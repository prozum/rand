#include "log.h"
#include <string.h>
#include "io.h"

//Prefix defines:
#define WARNING_PREFIX "W: "
#define ERROR_PREFIX "E: "
#define MSG_PREFIX "M: "

//logging_level defines which class(es) of errors that should be logged
level logging_level = LOG_NONE;

/*Toggles logging at the given level - must be called during start-up of drone!*/
void toggle_logging(level lvl) {
    //Write project-name and version to buffer
    const char *ver = strcat(", version: ", MAJOR_VERSION);
    serial_write_string(USB_TX, (sval_t *)(PROJECT_NAME, ver));

    logging_level = lvl;
}

/*Logs a message directly to serial output*/
void LOG(char *msg) {
    if(logging_level == LOG_ALL) {
        serial_write_string(USB_TX, (sval_t *)strcat(MSG_PREFIX, msg));
    }
}

/*Logs a warning directly to serial output*/
void LOG_WARNING(char msg[]) {
    if(logging_level > LOG_ONLY_ERRORS) {
        serial_write_string(USB_TX, (sval_t * )strcat(WARNING_PREFIX, msg));
    }
}

/*Logs an error directly to serial output.*/
void LOG_ERROR(char msg[]) {
    if(logging_level >= LOG_ONLY_ERRORS) {
        serial_write_string(USB_TX, (sval_t *) strcat(ERROR_PREFIX, msg));
    }
}