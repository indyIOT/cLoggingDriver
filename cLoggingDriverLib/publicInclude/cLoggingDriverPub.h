/** ***********************************************
 * @file cLoggingDriverPub.h
 * @brief Public interface for the logging driver
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "cLoggingConfig.h"
#include "commonTypes.h"
#include "commonMacros.h"

#ifndef C_LOGGING_DRIVER_PUB_H
#define C_LOGGING_DRIVER_PUB_H
#ifdef __cplusplus
extern "C" {
#endif

/*************************************** Typedefs **************************************/
/** 
 * @brief Structure that contains information about a log message.
 */
typedef struct
{
    uint16_t logMessageKey;
    uint16_t fileModuleEnum;
    uint16_t lineNumber;
    uint32_t singleParamValue;
    eLoggingType_t logType;
    uint16_t logMessageLength;    
    char * logMessage;
    uint16_t * logMessageCrc;
} sLoggingInfo_t;

#ifndef SCOMMON_LOG_FLAGS
#define SCOMMON_LOG_FLAGS
/** 
 * @brief Union that contains flags for the logging driver.
 * the flags are used to control the behavior of the logging driver. Set only at
 * initLoggingDriver() and not changed after that.
 */
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
#endif // SCOMMON_LOG_FLAGS

/**************************** HELPER MACROS ***********************************************/
#define LOG_CRITICAL( message, ... ) logMessage( THIS->_driverControl._driverInfo._moduleID, \
                                                    __LINE__, \
                                                    LOGGING_TYPE_CRITICAL, \
                                                    message, ##__VA_ARGS__ )
#define LOG_ERROR( message, ... )    logMessage( THIS->_driverControl._driverInfo._moduleID, \
                                                    __LINE__, \
                                                    LOGGING_TYPE_ERROR, \
                                                    message, ##__VA_ARGS__ )
#define LOG_WARNING( message, ... )  logMessage( THIS->_driverControl._driverInfo._moduleID, \
                                                    __LINE__, \
                                                    LOGGING_TYPE_WARNING, \
                                                    message, ##__VA_ARGS__ )
#define LOG_INFO( message, ... )     logMessage( THIS->_driverControl._driverInfo._moduleID, \
                                                    __LINE__, \
                                                    LOGGING_TYPE_INFO, message, ##__VA_ARGS__ )

/**************************** External Function Prototypes ********************************/
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
                         ... );


/**
 * @brief Function to get the number of log messages currently stored in the logging driver.
 * @param errorCount Pointer to a uint16_t variable to store the number of log messages.
 * @return An error if one occurrred.
 */
extern sErrorCompact_t getLogCount( uint16_t * const errorCount );

/**
 * @brief Function to clear all log messages from the logging driver.
 */
extern void clearLogMessages( void );

/**
 * @brief Function to print all log messages currently stored in the logging driver.
 */
extern void printAllLogMessages( void );

/**
 * @brief Function to initialize the logging driver. This should be called before any other functions are used.
 * @param readMemory Pointer to a function that reads memory for the logging driver. 
 *                   This is used to read the log information from the circular buffer.
 * @param writeMemory Pointer to a function for writing memory for the logging driver.
 * @param stdOutputFunction Pointer to a function for outputting log messages to the standard output.
 * @param scratchBuffer Pointer to a buffer that can be used for temporary storage of log messages.
 * @param logFlags A union of flags that control the behavior of the logging driver.
 * @param scratchBufferSize Variable that holds the size of the scratch buffer. * 
 * @param memoryAddress The starting address of the memory to be used by the logging driver.
 * @param memorySizeInBytes Size of the memory in bytes
 * @param maxLogCount The maximum number of log messages that can be stored in the logging driver.
 *                    regardless of memory.
 * @return sErrorCompact_t structure containing the error information if an error occurred.
 */
extern sErrorCompact_t initLoggingDriver( uint16_t * readMemory, 
                                          uint16_t * writeMemory,
                                          uint16_t * stdOutputFunction,
                                          uint8_t  * scratchBuffer,
                                          uLoggingFlags_t logFlags,
                                          size_t   const scratchBufferSize,
                                          uint32_t const memoryAddress,
                                          uint16_t const memorySizeInBytes,
                                          uint16_t const maxLogCount );

/**
 * @brief Function to get the logging driver information. This will return a structure containing the logging driver information.
 * @return sCommonDriverAccessorStruct_t structure containing the logging driver information.
 */
extern sCommonDriverAccessorStruct_t const * const getLoggingDriverInfo( void );


#ifdef __cplusplus
}  /* extern "C" */
#endif
#endif /* C_LOGGING_DRIVER_PUB_H */
