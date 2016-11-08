cmake_minimum_required(VERSION 2.8)
include(cmake/Arduino.cmake)

project(rand)

# Options
option(SAMPLES "Samples" OFF)
option(TESTS "Tests" OFF)
option(SERIAL_TARGETS "Serial Targets" OFF)
option(SIZE_TARGETS "Size Targets" OFF)

include_directories(src/lib)
avr_include_directories(src/lib)

add_subdirectory(src)

if(SAMPLES)
    add_subdirectory(samples)
endif()

if(SERIAL_TARGETS)
    setup_serial_targets()
endif()

if(TESTS)
    add_subdirectory(test_firmware)

    get_property(DEFINES GLOBAL PROPERTY TEST_FIRMWARE_DEFINES)
    get_property(PATHS GLOBAL PROPERTY TEST_FIRMWARE_PATHS)

    #message("PATHS: ${PATHS}")
    #message("DEFINES: ${DEFINES}")

    #externalproject_add(tests
    #        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test
    #        CMAKE_CACHE_DEFAULT_ARGS -DTEST_FIRMWARE_DEFINES:STRING=${DEFINES} -DTEST_FIRMWARE_PATHS:STRING=${PATHS}
    #        INSTALL_COMMAND "./unit/tests")
endif()
