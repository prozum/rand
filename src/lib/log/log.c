#include "log.h"
#include <string.h>
#include "io.h"

//Prefix defines:
#define WARNING_PREFIX "W: "
#define ERROR_PREFIX "E: "
#define MSG_PREFIX "M: "

typedef struct disabled_device_s {
    log_sender blocked_device;
    struct disabled_device *next;
} disabled_device;

disabled_device *head;

//logging_level defines which class(es) of errors that should be logged
level logging_level = LOG_NONE;

/*Toggles logging at the given level - must be called during start-up of drone!*/
void toggle_logging(level lvl) {
    //Write project-name and version to buffer
    const char *ver = strcat(", version: ", MAJOR_VERSION);
    serial_write_string(USB_TX, (sval_t *)(PROJECT_NAME, ver));

    logging_level = lvl;
}

int senderIgnored(log_sender sender) {
    disabled_device *itr = head;

    while(itr != NULL) {
        //see if the sender is in the list of blocked senders, return 'true' if it is.
        if(itr->blocked_device == sender) {
            return 1;
        }
        itr = itr->next;
    }

    //The sender was not in the list, return 'false'
    return 0;
}

/*Logs a message directly to serial output*/
void LOG(log_sender sender, char *msg) {
    if(!senderIgnored(sender) && logging_level == LOG_ALL) {
        serial_write_string(USB_TX, (sval_t *)strcat(MSG_PREFIX, msg));
    }
}

/*Logs a warning directly to serial output*/
void LOG_WARNING(log_sender sender, char *msg) {
    if(!senderIgnored(sender) && logging_level > LOG_ONLY_ERRORS) {
        serial_write_string(USB_TX, (sval_t * )strcat(WARNING_PREFIX, msg));
    }
}

/*Logs an error directly to serial output.*/
void LOG_ERROR(log_sender sender, char *msg) {
    if(!senderIgnored(sender) && logging_level >= LOG_ONLY_ERRORS) {
        serial_write_string(USB_TX, (sval_t *) strcat(ERROR_PREFIX, msg));
    }
}

void LOG_ERROR_BYPASS(char *msg) {
    serial_write_string(USB_TX, (sval_t *) strcat(ERROR_PREFIX, msg));
}

void disable_device(log_sender device) {
    //Run through list to find an available slot
    disabled_device *itr = head;
    while (itr != NULL) {
        //return if the device is already in the list.
        if(itr->blocked_device == device)
            return;

        itr = itr->next;
    }

    //Fill in the disable device on that spot
    disabled_device next = {.blocked_device = device, .next = NULL};
    itr = &next;
}