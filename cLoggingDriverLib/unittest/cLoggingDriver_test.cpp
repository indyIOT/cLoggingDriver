/** ***********************************************
 * @file cErrorDriver_test.cpp
 * @brief Unit tests for cErrorDriver.c
 * @author Anthony Garza
 * @copyright All rights reserved 2026
*************************************************/

#include <gtest/gtest.h>
#include <cstddef>
#include <cstdint>
#include "../publicInclude/cErrorDriverPub.h"
#include "../publicInclude/cErrorDriverConfig.h"
#include "../publicInclude/cCommonErrorCodes.h"

namespace 
{
    constexpr std::size_t kFakeMemoryWords = 256U;
    std::uint32_t gFakeMemory[kFakeMemoryWords] = { 0U };

    std::uint16_t fakeReadMemory( std::uint32_t address, std::uint8_t * const readValue, std::size_t readSize )
    {
        std::uint16_t returnValue = 0U;
        if( address < ( kFakeMemoryWords * sizeof( std::uint32_t ) ) )
        {
            if( readValue != nullptr && readSize != 0U )
            {
                if( readSize + address > ( kFakeMemoryWords * sizeof( std::uint32_t ) ) )
                {
                    readSize = ( kFakeMemoryWords * sizeof( std::uint32_t ) ) - address;
                }
                std::memcpy( readValue, &gFakeMemory[address], readSize );
                returnValue = static_cast<std::uint16_t>(readSize);
            }
        }

        return returnValue;
    }

    std::uint16_t fakeWriteMemory( std::uint32_t address, std::uint8_t * data, std::size_t writeLength  )
    {
        std::uint16_t returnValue = 0U;
        if( address < ( kFakeMemoryWords * sizeof( std::uint32_t ) ) )
        {
            if( writeLength + address > ( kFakeMemoryWords * sizeof( std::uint32_t ) ) )
            {
                writeLength = ( kFakeMemoryWords * sizeof( std::uint32_t ) ) - address;
            }

            std::memcpy( &gFakeMemory[address], data, writeLength );
            returnValue = static_cast<std::uint16_t>(writeLength);
        }
        return returnValue;
    }

    sErrorCompact_t fakeLogCallback( eLoggingType_t logType, uint16_t logKey, char const * const logMessage )
    {
        (void)logType;
        (void)logKey;
        (void)logMessage;
        sErrorCompact_t errorInfo = BLANK_ERROR_STRUCT;
        return errorInfo;
    }
} // namespace

TEST( cErrorDriver, initErrorDriver )
{
    sErrorCompact_t errorInfo = initErrorDriver(
        (readMemoryFunctionPtr_t)&fakeReadMemory,
        (writeMemoryFunctionPtr_t)&fakeWriteMemory,
        (logCallback_t)&fakeLogCallback,
        0U,
        sizeof( gFakeMemory )
    );
    
    EXPECT_EQ( ERROR_NONE, errorInfo._compact._errorCode );
}