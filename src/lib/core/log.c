#include <string.h>
#include "core/io.h"
#include "core/log.h"

//Prefix defines:
static const char* WARNING_PREFIX = "W: ";
static const char* ERROR_PREFIX = "E: ";
static const char* MSG_PREFIX = "M: ";

typedef struct disabled_device_node disabled_device;

struct disabled_device_node {
    log_sender blocked_device;
    disabled_device *next;
};

//Head for the list of disable devices
static disabled_device *head = NULL;
//logging_level defines which class(es) of errors that should be logged
static level logging_level = LOG_NONE;

/**
 * Toggles logging for the system at the given level.
 * @param lvl which classes of errors to log (may be LOG_ONLY_ERRORS, LOG_DEBUG, LOG_ALL, LOG_NONE)
 */
void toggle_logging(level lvl) {
    //Produce a message with version and project-name
    char init_msg[30];
    strcpy(init_msg, MAJOR_VERSION);
    strcat(init_msg, ", version: ");
    strcat(init_msg, PROJECT_NAME);

    //Set logging lvl
    logging_level = lvl;
    //Write the init-message to log (only goes through if logging_level is set to ALL).
    LOG(SENDER_BOARD, init_msg);
}

/**
 * Checks wether the given sender has been ignored.
 * @param sender
 * @return 0 if the sender has not been ignored, 1 if it has.
 */
uint8_t sender_ignored(log_sender sender) {
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

/**
 * Logs a standard message
 * @param sender is the module to log from
 * @param msg is the message to log.
 */
void LOG(log_sender sender, const char *msg) {
    if(!sender_ignored(sender) && logging_level == LOG_ALL) {
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, strcat(cpy, MSG_PREFIX));
    }
}

/**
 * Logs a warning
 * @param sender is the module to log from
 * @param msg  is the warning to log
 */
void LOG_WARNING(log_sender sender, const char *msg) {
    if(!sender_ignored(sender) && logging_level > LOG_ONLY_ERRORS) {
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, strcat(cpy, WARNING_PREFIX));
    }
}

/**
 * Logs an error
 * @param sender is the module to log from
 * @param msg is the error to log
 */
void LOG_ERROR(log_sender sender, const char *msg) {
    if(!sender_ignored(sender) && logging_level >= LOG_ONLY_ERRORS) {
        char cpy[strlen(msg) + 3];
        strcpy(cpy, msg);

        serial_write_string(USB_TX, strcat(cpy, ERROR_PREFIX));
    }
}

/**
 * Bypasses all filters an logs a serious error.
 * @param msg is the error to log.
 */
void LOG_ERROR_BYPASS(const char *msg) {
    char cpy[strlen(msg) + 3];
    strcpy(cpy, msg);

    serial_write_string(USB_TX, strcat(cpy, ERROR_PREFIX));
}

/**
 * Disables a module, blocking all future logs
 * @param device to disable.
 */
void disable_device(log_sender device) {
    disabled_device new_dev = {.blocked_device = device, .next = NULL};

    //Run through list to find an available slot
    disabled_device *ptr = head;

    while (ptr != NULL) {
        //return if the device is already in the list.
        if(ptr->blocked_device == device)
            return;

        ptr = ptr->next;
    }

    //Fill in the disable device on that spot
    *ptr = new_dev;
}

#if MOCK
uint8_t count_disabled_devices() {
    uint8_t devices = 0;
    disabled_device *ptr = head;

    while (ptr != NULL) {
        devices++;
        ptr = ptr->next;
    }

    return devices;
}
#endif //MOCK
