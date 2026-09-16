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