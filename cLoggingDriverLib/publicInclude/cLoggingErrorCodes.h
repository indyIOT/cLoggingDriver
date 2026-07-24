/** ***********************************************
 * @file cLoggingErrorCodes.h
 * @brief Public interface for the logging error codes
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "cErrorDriverPub.h"
#include "cErrorDriverConfig.h"
#ifndef C_LOGGING_ERROR_CODES_H
#define C_LOGGING_ERROR_CODES_H
#ifdef __cplusplus
extern "C" {
#endif

#ifdef ERROR_NONE
#undef ERROR_NONE
#endif



/** Enumeration of Logging Error Codes These will always be offset by the module number and will always be larger than 0x20 */
typedef enum 
{
} eLoggingErrorCodes_t;

/**
 * @brief Function to get the error message corresponding to a common error code.
 * @param errorCode The common error code to get the message for.
 * @param errorMessage Pointer to a buffer to store the error message.
 * @returns A pointer to the error message string.
 */
extern sErrorInfo_t getLoggingErrorMessageFromErrorCode( uint16_t const errorCode,
                                                        uint8_t const * errorMessage );

                                                        
#ifdef __cplusplus
}  /* extern "C" */
#endif

#endif /* C_LOGGING_ERROR_CODES_H */