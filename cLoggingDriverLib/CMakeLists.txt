# ##############################################################################
# CMakeLists.txt — cLoggingDriverLib
#
# Builds the logging driver library (cLoggingDriverLib) as either a static or shared
# library depending on the COMPILE_LOGGING_DRIVER_LIBRARY_STATIC flag set by the
# parent CMakeLists.txt.
#
# Library layout:
#   source/       — private implementation (.c files compiled into the library)
#   include/      — private headers (only visible inside this library)
#   publicInclude/— public API headers (propagated to all consumers via PUBLIC)
#
# Dependencies:
#   commonMacros  — header-only INTERFACE target providing shared project macros
#                   (AG_UNUSED, AG_ARRAY_LEN, AG_BIT, etc.)
#
# Version header:
#   cLoggingDriverVersion.h is auto-generated into the build tree on every
#   cmake --build invocation via generateVersion.cmake. It is written to:
#     <binary_dir>/generated/cLoggingDriverVersion.h
#   and exposes LOGGING_DRIVER_VERSION_MAJOR/MINOR/PATCH/BUILD_TYPE/STRING.
#   A stub is written at configure time so the file exists for dep scanning.
#
# Unit tests:
#   Conditionally compiled when UNIT_TESTS is ON and the test source file
#   unittest/cErrorDriver_test.cpp exists. Linked against GTest::gtest_main
#   and discovered automatically via gtest_discover_tests().
# ##############################################################################

# --- Version header setup -----------------------------------------------------
set(VERSION_HEADER_DIR  ${CMAKE_CURRENT_BINARY_DIR}/generated)
set(VERSION_HEADER_FILE ${VERSION_HEADER_DIR}/cLoggingDriverVersion.h)

if( COMPILE_LOGGING_DRIVER_LIBRARY_STATIC )
    set(LOGGING_DRIVER_BUILD_TYPE "STATIC")
else()
    set(LOGGING_DRIVER_BUILD_TYPE "DYNAMIC")
endif()

# Write a stub at configure time so the path exists and dependency scanning works
# before the real file is generated on the first build.
file(MAKE_DIRECTORY ${VERSION_HEADER_DIR})
if(NOT EXISTS ${VERSION_HEADER_FILE})
    file(WRITE ${VERSION_HEADER_FILE}
        "/* Stub — replaced at build time by generateVersion.cmake */\n"
        "#ifndef C_LOGGING_DRIVER_VERSION_H\n"
        "#define C_LOGGING_DRIVER_VERSION_H\n"
        "#endif /* C_LOGGING_DRIVER_VERSION_H */\n"
    )
endif()
# ------------------------------------------------------------------------------


if( COMPILE_LOGGING_DRIVER_LIBRARY_STATIC )
    add_library(${LOGGING_DRIVER_LIBRARY_NAME} STATIC
        source/cLoggingDriver.c
    )
else()
    add_library(${LOGGING_DRIVER_LIBRARY_NAME} SHARED
        source/cLoggingDriver.c
    )
endif()

target_include_directories(${LOGGING_DRIVER_LIBRARY_NAME}
    PRIVATE
        include
        source
    PUBLIC
        publicInclude
)

target_link_libraries(${LOGGING_DRIVER_LIBRARY_NAME}
    PUBLIC
        commonMacros
        cErrorDriverLib
)

# Expose the generated header directory so consumers can #include it
target_include_directories(${LOGGING_DRIVER_LIBRARY_NAME}
    PUBLIC
        ${VERSION_HEADER_DIR}
)

# Always regenerate cLoggingDriverVersion.h at every build invocation.
# add_custom_target runs unconditionally (no output tracking), ensuring a
# fresh timestamp in PATCH on every cmake --build call.
add_custom_target(GenerateLoggingDriverVersion ALL
    COMMAND ${CMAKE_COMMAND}
        -DVERSION_MAJOR=${PROJECT_VERSION_MAJOR}
        -DVERSION_MINOR=${PROJECT_VERSION_MINOR}
        -DVERSION_PATCH=${PROJECT_VERSION_PATCH}
        -DVERSION_BUILD_TYPE=${LOGGING_DRIVER_BUILD_TYPE}
        -DOUTPUT_FILE=${VERSION_HEADER_FILE}
        -P ${CMAKE_CURRENT_SOURCE_DIR}/generateVersion.cmake
    COMMENT "Regenerating cLoggingDriverVersion.h"
    VERBATIM
)

# Ensure the header exists before the library sources are compiled
add_dependencies(${LOGGING_DRIVER_LIBRARY_NAME} GenerateLoggingDriverVersion)


if( UNIT_TESTS AND EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/unittest/cLoggingDriver_test.cpp )
    add_executable(
        cLoggingDriverTest
        unittest/cLoggingDriver_test.cpp
    )

    target_include_directories(cLoggingDriverTest
        PRIVATE
            include
            source
    )

    target_link_libraries(
        cLoggingDriverTest
        ${LOGGING_DRIVER_LIBRARY_NAME}
        GTest::gtest_main
    )

    include(GoogleTest)
    gtest_discover_tests(cLoggingDriverTest)
endif()
