/** ***********************************************
 * @file cLoggingErrorCodes.c
 * @brief Implementation of logging error codes for the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "cLoggingErrorCodes.h"
#include "cErrorDriverPub.h"


/**
 * @brief Function to get the error message corresponding to a common error code.
 * @param errorCode The common error code to get the message for.
 * @param errorMessage Pointer to a buffer to store the error message.
 * @returns A pointer to the error message string.
 */
extern sErrorInfo_t getLoggingErrorMessageFromErrorCode( uint16_t const errorCode,
                                                        uint8_t const * errorMessage )
{
    sErrorInfo_t retValue = BLANK_ERROR_STRUCT;

    return ( retValue )
}