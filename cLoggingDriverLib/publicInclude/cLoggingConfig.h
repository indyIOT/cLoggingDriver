/** ***********************************************
 * @file cLoggingConfig.h
 * @brief Public Configuration for the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef C_LOGGING_DRIVER_CONFIG_H
#define C_LOGGING_DRIVER_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif
typedef enum
{
    LOGGING_TYPE_CRITICAL= 0U,
    LOGGING_TYPE_ERROR   = 1U,
    LOGGING_TYPE_WARNING = 2U,
    LOGGING_TYPE_INFO    = 3U,
    LOGGING_TYPE_DEBUG   = 4U
} eLoggingType_t;

typedef union
{
    /* data */
    uint8_t _allFlags;
    struct
    {
        uint8_t _logToConsole : 1;
        uint8_t _logToMemory : 1;
        uint8_t _logKeyAndSingleValueOnly : 1;
        eLoggingType_t loggingLevel : 3;
        uint8_t _reserved2 : 2;
    } _bits;
} uLoggingFlags_t;


#define MAX_LOGGING_DRIVER_MESSAGE_LENGTH 256U
#define MAX_LOGGING_DRIVER_MESSAGE_COUNT  100U
#define DEFAULT_LOG_LEVEL                 LOGGING_TYPE_DEBUG
#define DEFAULT_LOG_FLAGS                 { \
                                            ._bits._logToConsole = 1, \
                                            ._bits._logToMemory = 1, \
                                            ._bits._logKeyAndSingleValueOnly = 0, \
                                            ._bits.loggingLevel = DEFAULT_LOG_LEVEL, \
                                            ._bits._reserved2 = 0 }


#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* C_LOGGING_DRIVER_CONFIG_H */