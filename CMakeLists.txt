set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)
include(ExternalProject)

project(rand)

# Options
option(SAMPLES "Samples" ON)
option(TESTS "Tests" ON)
option(SERIAL_TARGETS "Serial Targets" ON)
option(SIZE_TARGETS "Size Targets" OFF)

#print_board_list()
#print_programmer_list()

include_directories(src/lib)

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

    #add_custom_target(test_test DEPENDS build/test_firmware/unit/io/pin0-pinmode-input.hex)
    #    message("PATHS: ${PATHS}")

    externalproject_add(tests
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test
            CMAKE_CACHE_DEFAULT_ARGS -DTEST_FIRMWARE_DEFINES:STRING=${DEFINES} -DTEST_FIRMWARE_PATHS:STRING=\"${PATHS}\"
            INSTALL_COMMAND "")
endif()
