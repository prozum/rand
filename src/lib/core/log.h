#ifndef RAND_LOG_H
#define RAND_LOG_H

/** @file log.h
 * \brief Log functions and data
 *
 * \addtogroup Log
 * @{
 */

#include <stdint.h>
#include <stddef.h>

#define MAJOR_VERSION "0.0\0" //!< Defines the version of the firmware, read as major.minor
#define PROJECT_NAME "RAND(IE)\0" //!< Defines the firmware's name

/**
 * An enum for storing the granularity of the logging system
 */
typedef enum log_level_e {
    LOG_ONLY_ERRORS = 0, LOG_DEBUG = 1, LOG_ALL = 2, LOG_NONE = -1
} log_level_t;
/**
 * An enum for storing all components that may use the logging-system
 */
typedef enum log_sender_e {
    SENDER_SONAR, SENDER_IR, SENDER_IO, SENDER_LASER, SENDER_FC, SENDER_MAP, SENDER_BOARD
} log_sender_t;

/**
 * A node for the list of ignored devices
 */
typedef struct disabled_device_node_s {
    log_sender_t blocked_device; //!< The blocked device
    struct disabled_device_node_s *next; //!< A pointer to the next device in the list
} disabled_device_t;

/**
 * Toggles logging for the system at the given level.
 * @param lvl which classes of errors to log (may be LOG_ONLY_ERRORS, LOG_DEBUG, LOG_ALL, LOG_NONE)
 */
void init_logging(log_level_t lvl);

/**
 * Logs a message
 * @param sender - The sender component
 * @param msg - The message to log
 */
void LOG(log_sender_t sender, const char *msg);
/**
 * Logs a warning
 * @param sender - The sender component
 * @param msg - The warning to log
 */
void WARNING(log_sender_t sender, const char *msg);
/**
 * Logs a serious warning, which bypasses the ignore-system
 * @param sender - The sender component
 * @param msg - The warning to log
 */
void SERIOUS_WARNING(log_sender_t sender, const char *msg);
/**
 * Logs an error to and causes the drone to emergency land
 * @param msg - The error to log
 */
void ERROR(const char *msg);
/**
 * Disables a device from the logging system
 * @param device - The device to disable
 */
void disable_device(log_sender_t device);

#if MOCK
/**
 * Counts the number of disabled devices
 * @return - The number of disabled devices
 */
uint8_t count_disabled_devices();
/**
 * Checks if a sender has been ignored by the logging system
 * @param sender - The sender to check for
 * @return - 0 or 1, meaning FALSE or TRUE repsectively
 */
uint8_t sender_ignored(log_sender_t sender);
/**
 * Clears the list of ignored devices
 */
void clear_list();

#endif //MOCK

#endif //RAND_LOG_H

//! @}