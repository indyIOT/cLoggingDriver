/** ***********************************************
 * @file cLoggingErrorCodes.c
 * @brief Implementation of logging error codes for the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "commonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************************** Type definitions ****************************/


/********************************Static functions Prototypes *************/


/******************************** Static Global Variables **********************/
static const uint8_t moduleName[] = "cLoggingErrors";
#define MODULE_ID 15856

/**************************** HELPER MACROS ************************************/
#ifndef ERROR_NONE
#define ERROR_NONE 0U
#endif

#ifndef NO_ERROR
#define NO_ERROR 0U
#endif

/****************************** Function implementations ***************/
/**
 * @brief Function to get the error message corresponding to a common error code.
 * @param errorCode The common error code to get the message for.
 * @param errorMessage Pointer to a buffer to store the error message.
 * @returns A pointer to the error message string.
 */
sErrorCompact_t getLoggingErrorMessageFromErrorCode( uint16_t const errorCode,
                                                     uint8_t const * errorMessage )
{
    sErrorCompact_t retValue = BLANK_ERROR_STRUCT;

    return ( retValue )
}

/************************ Static Function Implementations ***************/

#ifdef __cplusplus
}  /* extern "C" */
#endif
