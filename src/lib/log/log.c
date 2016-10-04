#include <string.h>
#include "io.h"
#include "log.h"

//Prefix defines:
static const char* WARNING_PREFIX = "W: ";
static const char* ERROR_PREFIX = "E: ";
static const char* MSG_PREFIX = "M: ";

typedef struct disabled_device_node {
    log_sender blocked_device;
    struct disabled_device *next;
} disabled_device;

//Head for the list of disable devices
static disabled_device *head = NULL;
//logging_level defines which class(es) of errors that should be logged
static level logging_level = LOG_NONE;

/**
 * Toggles logging for the system at the given level.
 * @param lvl which classes of errors to log (may be LOG_ONLY_ERRORS, LOG_DEBUG, LOG_ALL, LOG_NONE)
 */
void toggle_logging(level lvl) {
    //Write project-name and version to buffer
    char init_msg[30];
    strcpy(init_msg, MAJOR_VERSION);
    strcat(init_msg, ", version: ");
    strcat(init_msg, PROJECT_NAME);
    serial_write_string(USB_TX, (sval_t *) init_msg);

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
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, (sval_t *)strcat(cpy, MSG_PREFIX));
    }
}

/*Logs a warning directly to serial output*/
void LOG_WARNING(log_sender sender, char *msg) {
    if(!senderIgnored(sender) && logging_level > LOG_ONLY_ERRORS) {
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, (sval_t * )strcat(cpy, WARNING_PREFIX));
    }
}

/*Logs an error directly to serial output.*/
void LOG_ERROR(log_sender sender, char *msg) {
    if(!senderIgnored(sender) && logging_level >= LOG_ONLY_ERRORS) {
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, (sval_t *) strcat(cpy, ERROR_PREFIX));
    }
}

void LOG_ERROR_BYPASS(char *msg) {
    char cpy[strlen(msg) + 3];
    strcpy(cpy, msg);

    serial_write_string(USB_TX, (sval_t *) strcat(cpy, ERROR_PREFIX));
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
    itr->blocked_device = device;
    itr->next = NULL;
}