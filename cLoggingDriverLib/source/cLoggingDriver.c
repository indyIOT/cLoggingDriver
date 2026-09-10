/** ***********************************************
 * @file cLoggingDriver.c
 * @brief Implementation of the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include "commonMacros.h"
#include "cLoggingDriver.h"
#include "cLoggingDriverPub.h"
#include "cLoggingDriverVersion.h"
#include "cLoggingErrorCodes.h"


#ifdef __cplusplus
extern "C" {
#endif

/******************************** Type definitions ****************************/
typedef struct
{
    uint16_t * readMemory; /* Pointer to a function that reads memory for the error driver */
    uint16_t * writeMemory; /* Pointer to a function for writing memory for the error driver */
    uint16_t * stdOutputFunction; /* Pointer to a function for outputting log messages to the standard output */
    uint32_t memoryAddress; /* The starting address of the memory to be used by the error driver */
    uint16_t memorySizeInBytes; /* Size of the memory in bytes */
    uint16_t maxLogCount; /* The maximum number of log messages that can be stored in the logging driver */
    uint8_t * scratchBuffer; /* Pointer to a buffer that can be used for temporary storage of log messages */
    size_t scratchBufferSize; /* Variable that holds the size of the scratch buffer */
    uint8_t const * const moduleName; /* Name of the module */
    uint16_t moduleID; /* ID of the module */
    bool isInitialized; /* Whether or not the error driver has been initialized */
} sLoggingDriverControlStruct_t;

/********************************Static functions Prototypes *************/


/******************************** Static Global Variables **********************/
static const uint8_t moduleName[] = "cLoggingDriver";
#define MODULE_ID 10975











static sLoggingDriverControlStruct_t loggingDriverControl = { NULL, NULL, NULL, 0, 0, 0, NULL, 0, moduleName, 0, false };
static sLoggingDriverControlStruct_t * const THIS = &loggingDriverControl;


/**************************** HELPER MACROS ************************************/
#ifndef ERROR_NONE
#define ERROR_NONE 0U
#endif

#ifndef NO_ERROR
#define NO_ERROR 0U
#endif

/****************************** Function implementations ***************/
/**
 * @brief Function to initialize the logging driver. This should be called before any other functions are used.
 * @param readMemory Pointer to a function that reads memory for the logging driver.
 *                  This is used to read the log information from the circular buffer.
 * @param writeMemory Pointer to a function for writing memory for the logging driver.
 * @param stdOutputFunction Pointer to a function for outputting log messages to the standard output
 * @param scratchBuffer Pointer to a buffer that can be used for temporary storage of log messages.
 * @param scratchBufferSize Variable that holds the size of the scratch buffer.
 * @param memoryAddress The starting address of the memory to be used by the logging driver.
 * @param memorySizeInBytes Size of the memory in bytes
 * @param maxLogCount The maximum number of log messages that can be stored in the logging driver.
 * @return sErrorCompact_t structure containing the error information if an error occurred.
 */
sErrorCompact_t initLoggingDriver( uint16_t * readMemory, 
                                uint16_t * writeMemory,
                                uint16_t * stdOutputFunction,
                                uint8_t  * scratchBuffer,
                                eLoggingType_t logLevel,
                                eLoggingFlags_t logFlags,
                                size_t   const scratchBufferSize,
                                uint32_t const memoryAddress,
                                uint16_t const memorySizeInBytes,
                                uint16_t const maxLogCount )
{
    sErrorCompact_t retValue = BLANK_ERROR_STRUCT;
    if( THIS->isInitialized == false )
    {
        if( logFlags & )
        if( readMemory == NULL || writeMemory == NULL || stdOutputFunction == NULL || scratchBuffer == NULL )
        {
            retValue = CREATE_ERROR( ERROR_NULL_POINTER, "" );
            LOG_CRITICAL( "Logging Driver Initialization Failed: Read or Write Memory function pointer is NULL." );
        }
        else
        {
            if( memorySizeInBytes < sizeof( sLoggingInfo_t ) * maxLogCount )
            {
                retValue = CREATE_ERROR( ERROR_INVALID_PARAMETER, "" );
                LOG_CRITICAL( "Logging Driver Initialization Failed: Memory size is too small. Minimum size required is %u bytes.", sizeof( sLoggingInfo_t ) * maxLogCount );
            }
            else
            {
                THIS->readMemory = readMemory;
                THIS->writeMemory = writeMemory;
                THIS->memoryAddress = memoryAddress;
                THIS->memorySizeInBytes = memorySizeInBytes;
                THIS->isInitialized = true;
            }
        }
    }
    else
    {
        retValue = CREATE_ERROR( ERROR_ALREADY_INITIALIZED, "" );
    }
    return retValue;
}

/**
 * @brief Function to log a message to the logging driver.
 * @note If Logging type is error or critical, the logMessage function will
 * not create new errors that could cause a recurrsion.
 * @param fileModuleEnum The module ID where the log message is coming from.
 * @param lineNumber The line number where the log message is coming from.
 * @param logType The type of log message (e.g. error, warning, info, debug).
 * @param logFlags The flags for the log message (e.g. log to console, log to memory, log to both).
 * @param logMessage The log message to be logged.
 * @return sErrorCompact_t structure containing the error information if an error occurred.
 */
sErrorCompact_t logMessage( uint16_t fileModuleEnum, 
                         uint16_t lineNumber,
                         eLoggingType_t logType,
                         char const * const logMessage, 
                         ... )

{
    sErrorCompact_t retValue = BLANK_ERROR_STRUCT;

    return retValue;
}

/************************ Static Function Implementations ***************/
/** 
 * @brief Get the name of the logging module.
 * @return Pointer to a string containing the module name.
 */
uint8_t const * const getModuleName( void )
{
    return (uint8_t const * const)moduleName;
}

/**
 * @brief Get the version string of the logging module.
 * @return Pointer to a string containing the version of the module.
 */
uint8_t const * getModuleVersionString( void )
{
    return (uint8_t const *)ERROR_DRIVER_VERSION_STRING;
}


#ifdef __cplusplus
}  /* extern "C" */
#endif
