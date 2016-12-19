#include "core/log.h"

#include <stdlib.h>
#include <string.h>

#include "core/io.h"

// Prefix defines:
#define PREFIX_SIZE 4
const char WARNING_PREFIX[PREFIX_SIZE] = "W: ";
const char ERROR_PREFIX[PREFIX_SIZE] = "E: ";
const char MSG_PREFIX[PREFIX_SIZE] = "M: ";

// Head for the list of disable devices
static disabled_device_t *head = NULL;
// Logging_level defines which class(es) of errors that should be logged
static log_level_t logging_level = LOG_NONE;

void init_logging(log_level_t lvl) {
#if MOCK
    // Produce a message with version and project-name
    char init_msg[30];
    strcpy(init_msg, MAJOR_VERSION);
    strcat(init_msg, ", version: ");
    strcat(init_msg, PROJECT_NAME);

    // Set logging lvl
    logging_level = lvl;
    // Write the init-message to log (only goes through if logging_level is set to ALL).
    LOG(SENDER_BOARD, init_msg);
#endif
}

uint8_t sender_ignored(log_sender_t sender) {
    disabled_device_t *itr = head;

    while (itr != NULL) {
        // See if the sender is in the list of blocked senders, return 'true' if it is.
        if (itr->blocked_device == sender) {
            return 1;
        }
        itr = itr->next;
    }

    // The sender was not in the list, return 'false'
    return 0;
}

void LOG(log_sender_t sender, const char *msg) {
#ifndef MOCK
    if (!sender_ignored(sender) && logging_level == LOG_ALL) {
        char tmp[strlen(msg) + PREFIX_SIZE];
        strcpy(tmp, msg);

        serial_write_string(USB_TX, strcat(tmp, MSG_PREFIX));
    }
#endif // !MOCK
#if MOCK
    printf("%s%s\n", "MESSAGE: ", msg);
#endif // MOCK
}

void WARNING(log_sender_t sender, const char *msg) {
#ifndef MOCK
    if (!sender_ignored(sender) && logging_level > LOG_ONLY_ERRORS) {
        char tmp[strlen(msg) + PREFIX_SIZE];
        strcpy(tmp, msg);

        serial_write_string(USB_TX, strcat(tmp, WARNING_PREFIX));
    }
#endif //! MOCK
#if MOCK
    printf("%s%s\n", "WARNING: ", msg);
#endif // MOCK
}

void SERIOUS_WARNING(log_sender_t sender, const char *msg) {
#ifndef MOCK
    if (!sender_ignored(sender) && logging_level >= LOG_ONLY_ERRORS) {
        char tmp[strlen(msg) + PREFIX_SIZE];
        strcpy(tmp, msg);

        serial_write_string(USB_TX, strcat(tmp, ERROR_PREFIX));
    }
#endif //! MOCK
#if MOCK
    printf("%s%s\n", "SERIOUS WARNING: ", msg);
#endif // MOCK
}

void ERROR(const char *msg) {
#ifndef MOCK
// TODO: Add code for safely landing drone
/*char cpy[strlen(msg) + PREFIX_SIZE];
strcpy(cpy, msg);

serial_write_string(USB_TX, strcat(cpy, ERROR_PREFIX));*/
#endif //! MOCK
#if MOCK
    printf("%s%s\n", "ERROR: ", msg);
#endif // MOCK
}

void disable_device(log_sender_t device) {
    disabled_device_t *new_dev = malloc(sizeof(disabled_device_t));
    ;
    new_dev->blocked_device = device;
    new_dev->next = NULL;

    // Run through list to find an available slot
    if (!head) {
        head = new_dev;
        return;
    }

    disabled_device_t *ptr = head;
    while (ptr->next) {
        // return if the device is already in the list.
        if (ptr->blocked_device == device)
            return;

        ptr = ptr->next;
    }
    if (ptr->blocked_device != device)
        ptr->next = new_dev;
    else
        free(new_dev);
}

#if MOCK
uint8_t count_disabled_devices() {
    uint8_t devices = 0;
    disabled_device_t *ptr = head;

    while (ptr != NULL) {
        devices++;
        ptr = ptr->next;
    }

    return devices;
}

void clear_list() {
    disabled_device_t *next;

    if (!head)
        return;

    while (head->next) {
        next = head->next;
        free(head);
        head = next;
    }

    if (head) {
        free(head);
        head = NULL;
    }
}

#endif // MOCK
