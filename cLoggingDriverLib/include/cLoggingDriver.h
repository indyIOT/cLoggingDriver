/** ***********************************************
 * @file cLoggingDriver.h
 * @brief Private interface for the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#ifndef C_LOGGING_DRIVER_H
#define C_LOGGING_DRIVER_H
#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Function to get the error message corresponding to a common error code.
 * @param errorCode The common error code to get the message for.
 * @param errorMessage Pointer to a buffer to store the error message.
 * @returns A pointer to the error message string.
 */
extern sErrorCompact_t getLoggingErrorMessageFromErrorCode( uint16_t const errorCode,
                                                        uint8_t const * errorMessage );
                                                        
#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* C_LOGGING_DRIVER_H */
