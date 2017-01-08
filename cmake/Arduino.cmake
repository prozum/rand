#=============================================================================#
# generate_arduino_firmware(name
#      [BOARD board_id]
#      [SKETCH sketch_path |
#       SRCS  src1 src2 ... srcN]
#      [HDRS  hdr1 hdr2 ... hdrN]
#      [LIBS  lib1 lib2 ... libN]
#      [PORT  port]
#      [SERIAL serial_cmd]
#      [PROGRAMMER programmer_id]
#      [AFLAGS flags]
#      [NO_AUTOLIBS]
#      [MANUAL])
#
#=============================================================================#
#
#   generaters firmware and libraries for Arduino devices
#
# The arguments are as follows:
#
#      name           # The name of the firmware target         [REQUIRED]
#      BOARD          # Board name (such as uno, mega2560, ...) [REQUIRED]
#      SKETCH         # Arduino sketch [must have SRCS or SKETCH]
#      SRCS           # Sources        [must have SRCS or SKETCH]
#      HDRS           # Headers 
#      LIBS           # Libraries to link
#      ARDLIBS        # Arduino libraries to link (Wire, Servo, SPI, etc)
#      PORT           # Serial port (enables upload support)
#      SERIAL         # Serial command for serial target
#      PROGRAMMER     # Programmer id (enables programmer support)
#      AFLAGS         # Avrdude flags for target
#      NO_AUTOLIBS    # Disables Arduino library detection
#      MANUAL         # (Advanced) Only use AVR Libc/Includes
#
# Here is a short example for a target named test:
#    
#       generate_arduino_firmware(
#           NAME test
#           SRCS test.cpp 
#                test2.cpp
#           HDRS test.h test2.h
#           BOARD uno)
#
# Alternatively you can specify the option by variables:
#
#       set(test_SRCS test.cpp test2.cpp)
#       set(test_HDRS test.h test2.h
#       set(test_BOARD uno)
#
#       generate_arduino_firmware(test)
#
# All variables need to be prefixed with the target name (${TARGET_NAME}_${OPTION}).
#
#=============================================================================#
# generate_avr_firmware(name
#      [BOARD board_id]
#       SRCS  src1 src2 ... srcN]
#      [HDRS  hdr1 hdr2 ... hdrN]
#      [LIBS  lib1 lib2 ... libN]
#      [PORT  port]
#      [SERIAL serial_cmd]
#      [PROGRAMMER programmer_id]
#      [AFLAGS flags])
#=============================================================================#
#
#   generaters firmware and libraries for AVR devices
#   it simply calls generate_arduino_firmware() with NO_AUTOLIBS and MANUAL
#
# The arguments are as follows:
#
#      name           # The name of the firmware target         [REQUIRED]
#      BOARD          # Board name (such as uno, mega2560, ...) [REQUIRED]
#      SRCS           # Sources                                 [REQUIRED]
#      HDRS           # Headers 
#      LIBS           # Libraries to link
#      PORT           # Serial port (enables upload support)
#      SERIAL         # Serial command for serial target
#      PROGRAMMER     # Programmer id (enables programmer support)
#      AFLAGS         # Avrdude flags for target
#
# Here is a short example for a target named test:
#    
#       generate_avr_firmware(
#           NAME test
#           SRCS test.cpp 
#                test2.cpp
#           HDRS test.h test2.h
#           BOARD uno)
#
# Alternatively you can specify the option by variables:
#
#       set(test_SRCS test.cpp test2.cpp)
#       set(test_HDRS test.h test2.h
#       set(test_BOARD uno)
#
#       generate_avr_firmware(test)
#
# All variables need to be prefixed with the target name (${TARGET_NAME}_${OPTION}).
#
#=============================================================================#
# generate_arduino_library(name
#      [BOARD board_id]
#      [SRCS  src1 src2 ... srcN]
#      [HDRS  hdr1 hdr2 ... hdrN]
#      [LIBS  lib1 lib2 ... libN]
#      [NO_AUTOLIBS]
#      [MANUAL])
#=============================================================================#
#   generaters firmware and libraries for Arduino devices
#
# The arguments are as follows:
#
#      name           # The name of the firmware target         [REQUIRED]
#      BOARD          # Board name (such as uno, mega2560, ...) [REQUIRED]
#      SRCS           # Sources                                 [REQUIRED]
#      HDRS           # Headers 
#      LIBS           # Libraries to link
#      NO_AUTOLIBS    # Disables Arduino library detection
#      MANUAL         # (Advanced) Only use AVR Libc/Includes
#
# Here is a short example for a target named test:
#    
#       generate_arduino_library(
#           NAME test
#           SRCS test.cpp 
#                test2.cpp
#           HDRS test.h test2.h
#           BOARD uno)
#
# Alternatively you can specify the option by variables:
#
#       set(test_SRCS test.cpp test2.cpp)
#       set(test_HDRS test.h test2.h
#       set(test_BOARD uno)
#
#       generate_arduino_library(test)
#
# All variables need to be prefixed with the target name (${TARGET_NAME}_${OPTION}).
#
#=============================================================================#
# generate_avr_library(name
#      [BOARD board_id]
#      [SRCS  src1 src2 ... srcN]
#      [HDRS  hdr1 hdr2 ... hdrN]
#      [LIBS  lib1 lib2 ... libN])
#=============================================================================#
#   generaters firmware and libraries for AVR devices
#   it simply calls generate_arduino_library() with NO_AUTOLIBS and MANUAL
#
# The arguments are as follows:
#
#      name           # The name of the firmware target         [REQUIRED]
#      BOARD          # Board name (such as uno, mega2560, ...) [REQUIRED]
#      SRCS           # Sources                                 [REQUIRED]
#      HDRS           # Headers 
#      LIBS           # Libraries to link
#
# Here is a short example for a target named test:
#    
#       generate_avr_library(
#           NAME test
#           SRCS test.cpp 
#                test2.cpp
#           HDRS test.h test2.h
#           BOARD uno)
#
# Alternatively you can specify the option by variables:
#
#       set(test_SRCS test.cpp test2.cpp)
#       set(test_HDRS test.h test2.h
#       set(test_BOARD uno)
#
#       generate_avr_library(test)
#
# All variables need to be prefixed with the target name (${TARGET_NAME}_${OPTION}).
#
#=============================================================================#
# generate_arduino_example(name
#                          LIBRARY library_name
#                          EXAMPLE example_name
#                          [BOARD  board_id]
#                          [PORT port]
#                          [SERIAL serial command]
#                          [PORGRAMMER programmer_id]
#                          [AFLAGS avrdude_flags])
#=============================================================================#
#
#        name         - The name of the library example        [REQUIRED]
#        LIBRARY      - Library name                           [REQUIRED]
#        EXAMPLE      - Example name                           [REQUIRED]
#        BOARD        - Board ID
#        PORT         - Serial port [optional]
#        SERIAL       - Serial command [optional]
#        PROGRAMMER   - Programmer id (enables programmer support)
#        AFLAGS       - Avrdude flags for target
#
# Creates a example from the specified library.
#
#
#=============================================================================#
# print_board_list()
#=============================================================================#
#
# Print list of detected Arduino Boards.
#
#=============================================================================#
# print_programmer_list()
#=============================================================================#
#
# Print list of detected Programmers.
#
#=============================================================================#
# print_programmer_settings(PROGRAMMER)
#=============================================================================#
#
#        PROGRAMMER - programmer id
#
# Print the detected Programmer settings.
#
#=============================================================================#
# print_board_settings(ARDUINO_BOARD)
#=============================================================================#
#
#        ARDUINO_BOARD - Board id
#
# Print the detected Arduino board settings.
#
#=============================================================================#
# Configuration Options
#=============================================================================#
#
# ARDUINO_SDK_PATH            - Arduino SDK Path
# AVRDUDE_PROGRAM     - Full path to avrdude programmer
# AVRDUDE_CONFIG_PATH - Full path to avrdude configuration file
#
# AVR_C_FLAGS             - C compiler flags
# AVR_CXX_FLAGS           - C++ compiler flags
# AVR_LINKER_FLAGS        - Linker flags
#
# AVR_DEFAULT_BOARD      - Default AVR Board ID when not specified.
# AVR_DEFAULT_PORT       - Default AVR port when not specified.
# AVR_DEFAULT_SERIAL     - Default AVR Serial command when not specified.
# AVR_DEFAULT_PROGRAMMER - Default AVR Programmer ID when not specified.
#
#
# ARDUINO_FOUND       - Set to True when the Arduino SDK is detected and configured.
# ARDUINO_SDK_VERSION - Set to the version of the detected Arduino SDK (ex: 1.0)

#=============================================================================#
# Author: Tomasz Bogdal (QueezyTheGreat)
# Home:   https://github.com/queezythegreat/arduino-cmake
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this file,
# You can obtain one at http://mozilla.org/MPL/2.0/.
#=============================================================================#
cmake_minimum_required(VERSION 2.8.5)
include(CMakeParseArguments)


#=============================================================================#
#                           User Functions                                    
#=============================================================================#

#=============================================================================#
# [PUBLIC/USER]
#
# print_board_list()
#
# see documentation at top
#=============================================================================#
function(PRINT_BOARD_LIST)
    foreach (PLATFORM ${ARDUINO_PLATFORMS})
        if (${PLATFORM}_BOARDS)
            message(STATUS "${PLATFORM} Boards:")
            print_list(${PLATFORM}_BOARDS)
            message(STATUS "")
        endif ()
    endforeach ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#
# print_programmer_list()
#
# see documentation at top
#=============================================================================#
function(PRINT_PROGRAMMER_LIST)
    foreach (PLATFORM ${ARDUINO_PLATFORMS})
        if (${PLATFORM}_PROGRAMMERS)
            message(STATUS "${PLATFORM} Programmers:")
            print_list(${PLATFORM}_PROGRAMMERS)
        endif ()
        message(STATUS "")
    endforeach ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#
# print_programmer_settings(PROGRAMMER)
#
# see documentation at top
#=============================================================================#
function(PRINT_PROGRAMMER_SETTINGS PROGRAMMER)
    if (${PROGRAMMER}.SETTINGS)
        message(STATUS "Programmer ${PROGRAMMER} Settings:")
        print_settings(${PROGRAMMER})
    endif ()
endfunction()

# [PUBLIC/USER]
#
# print_board_settings(ARDUINO_BOARD)
#
# see documentation at top
function(PRINT_BOARD_SETTINGS ARDUINO_BOARD)
    if (${ARDUINO_BOARD}.SETTINGS)
        message(STATUS "Arduino ${ARDUINO_BOARD} Board:")
        print_settings(${ARDUINO_BOARD})
    endif ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
# see documentation at top
#=============================================================================#
function(GENERATE_AVR_LIBRARY INPUT_NAME)
    message(STATUS "Generating ${INPUT_NAME}")
    parse_generator_arguments(${INPUT_NAME} INPUT
            "MOCK"                # Options
            "BOARD"           # One Value Keywords
            "SRCS;HDRS;LIBS"  # Multi Value Keywords
            ${ARGN})

    if (NOT INPUT_BOARD)
        set(INPUT_BOARD ${ARDUINO_DEFAULT_BOARD})
    endif ()
    required_variables(VARS INPUT_SRCS INPUT_BOARD MSG "must define for target ${INPUT_NAME}")

    set(ALL_SRCS ${INPUT_SRCS} ${INPUT_HDRS})
    get_sources_paths(ALL_SRCS)

    # C flags
    get_avr_flags(COMPILE_FLAGS ${INPUT_BOARD} "${INPUT_LIBS}" True)

    # Setup target
    set(TARGET_AVR_NAME "${INPUT_NAME}-avr")
    add_custom_target("${TARGET_AVR_NAME}" COMMAND ""
            COMMENT "Building AVR Library: ${TARGET_AVR_NAME}")

    # Add dependencies
    foreach (LIB ${INPUT_LIBS})
        add_dependencies(${TARGET_AVR_NAME} "${LIB}-avr")
    endforeach ()

    # Build object files
    foreach (SRC ${ALL_SRCS})
        get_filename_component(OBJ_NAME ${SRC} NAME_WE)
        add_custom_command(TARGET ${TARGET_AVR_NAME}
                COMMAND ${AVR_C_COMPILER}
                ARGS ${COMPILE_FLAGS} ${SRC} -c -o ${CMAKE_CURRENT_BINARY_DIR}/${OBJ_NAME}.o
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
                COMMENT "Compiling object file for ${SRC}")
        list(APPEND OBJS "${CMAKE_CURRENT_BINARY_DIR}/${OBJ_NAME}.o")
    endforeach ()

    # Build static lib
    set(AVR_AR_FLAGS "rcs" "-o" "${AVR_LIB_PATH}/lib${INPUT_NAME}.a")
    add_custom_command(TARGET ${TARGET_AVR_NAME}
            COMMAND ${AVR_AR}
            ARGS ${AVR_AR_FLAGS} ${OBJS}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Create archive")


    # Mock lib
    if (INPUT_MOCK)
        add_library("${INPUT_NAME}" ${ALL_SRCS})
        if ("${INPUT_BOARD}" STREQUAL "uno")
            add_definitions(-D__AVR_ATmega328P__)
        elseif (${INPUT_BOARD} STREQUAL "mega")
            add_definitions(-D__AVR_ATmega1280__)
        else ()
            message(FATAL_ERROR "Board '${INPUT_BOARD}' not supported!")
        endif ()
        add_definitions(-DMOCK)
        target_link_libraries(${INPUT_NAME} "${INPUT_LIBS}")
    endif ()

endfunction()


#=============================================================================#
# [PUBLIC/USER]
# see documentation at top
#=============================================================================#
function(GENERATE_AVR_FIRMWARE INPUT_NAME)
    string(TOLOWER ${INPUT_NAME} INPUT_NAME)
    parse_generator_arguments(${INPUT_NAME} INPUT
            "TEST"                                  # Options
            "BOARD;PORT;SKETCH;PROGRAMMER"          # One Value Keywords
            "SERIAL;SRCS;HDRS;LIBS;ARDLIBS;AFLAGS"  # Multi Value Keywords
            ${ARGN})

    # Set name for test firmware
    if (INPUT_TEST)
        set(INPUT_NAME "test-fw-${INPUT_NAME}")
    endif ()

    message(STATUS "Generating ${INPUT_NAME}")

    if (NOT INPUT_BOARD)
        set(INPUT_BOARD ${ARDUINO_DEFAULT_BOARD})
    endif ()
    if (NOT INPUT_PORT)
        set(INPUT_PORT ${ARDUINO_DEFAULT_PORT})
    endif ()
    if (NOT INPUT_SERIAL)
        set(INPUT_SERIAL ${ARDUINO_DEFAULT_SERIAL})
    endif ()
    if (NOT INPUT_PROGRAMMER)
        set(INPUT_PROGRAMMER ${ARDUINO_DEFAULT_PROGRAMMER})
    endif ()
    required_variables(VARS INPUT_SRCS INPUT_BOARD MSG "must define for target ${INPUT_NAME}")

    set(ALL_SRCS ${INPUT_SRCS} ${INPUT_HDRS})
    get_sources_paths(ALL_SRCS)

    setup_avr_target(${INPUT_NAME} ${INPUT_BOARD} "${ALL_SRCS}" "${INPUT_LIBS}" "${LIB_DEP_INCLUDES}" "" "${INPUT_TEST}")

    if (INPUT_PORT)
        setup_arduino_upload(${INPUT_BOARD} ${INPUT_NAME} ${INPUT_PORT} "${INPUT_PROGRAMMER}" "${INPUT_AFLAGS}")
    elseif (NOT INPUT_TEST)
        # Detect port
        if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
            file(GLOB INPUT_PORTS /dev/ttyACM*)
        elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
            file(GLOB INPUT_PORTS /dev/cu.usbmodem*)
        else ()
          message(WARNING "${CMAKE_HOST_SYSTEM_NAME} port detection not supported yet.")
        endif ()

        if (INPUT_PORTS)
            list(SORT INPUT_PORTS)
            list(GET INPUT_PORTS 0 INPUT_PORT)
            message("-- * Detected port: ${INPUT_PORT}")
            setup_arduino_upload(${INPUT_BOARD} ${INPUT_NAME} ${INPUT_PORT} "${INPUT_PROGRAMMER}" "${INPUT_AFLAGS}")
        endif ()
    endif ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#=============================================================================#
function(GET_SOURCES_PATHS VAR_SRCS)
    foreach (SRC ${${VAR_SRCS}})
        if (EXISTS ${SRC})
            list(APPEND SRCS ${SRC})
        elseif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${SRC})
            list(APPEND SRCS ${CMAKE_CURRENT_SOURCE_DIR}/${SRC})
        elseif (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/${SRC})
            list(APPEND SRCS ${CMAKE_CURRENT_BINARY_DIR}/${SRC})
        else ()
            message(FATAL_ERROR "Cannot find file: ${SRC}")
        endif ()
    endforeach ()
    set(${VAR_SRCS} ${SRCS} PARENT_SCOPE)
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#=============================================================================#
function(LOAD_TEST_FIRMWARE_DEFINES)
    get_property(DEFINES GLOBAL PROPERTY TEST_FIRMWARE_DEFINES)
    get_property(PATHS GLOBAL PROPERTY TEST_FIRMWARE_PATHS)

    list(LENGTH DEFINES LENGTH)
    math(EXPR LENGTH "${LENGTH} - 1")
    foreach (ITER RANGE ${LENGTH})
        list(GET DEFINES ${ITER} DEFINE)
        list(GET PATHS ${ITER} PATH)
        add_definitions(-D${DEFINE}=\"${PATH}\")
    endforeach ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#=============================================================================#
function(ADD_TEST_DEPENDENCIES TEST_TARGET)
    get_property(TEST_FWS GLOBAL PROPERTY TEST_FIRMWARE_DEFINES)

    foreach (TEST_FW ${TEST_FWS})
        string(TOLOWER ${TEST_FW} TEST_FW)
        string(REPLACE "_" "-" TEST_FW ${TEST_FW})
        add_dependencies(${TEST_TARGET} ${TEST_FW})
    endforeach ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
#=============================================================================#
function(AVR_INCLUDE_DIRECTORIES)
    get_property(INC_DIRS DIRECTORY PROPERTY AVR_INCLUDE_DIRECTORIES)

    math(EXPR LENGTH "${ARGC} - 1")
    foreach (ITER RANGE ${LENGTH})
        set(FULL_PATH "${CMAKE_CURRENT_SOURCE_DIR}/${ARGV${ITER}}")
        list(APPEND INC_DIRS "${FULL_PATH}")
    endforeach ()

    set_property(GLOBAL PROPERTY AVR_INCLUDE_DIRECTORIES ${INC_DIRS})
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# get_avr_flags(COMPILE_FLAGS LINK_FLAGS BOARD_ID MANUAL)
#
#       COMPILE_FLAGS_VAR -Variable holding compiler flags
#       BOARD_ID - The board id name
#       LIBS - List of libraries to link
#       FOR_LIBRARY - Get flags for library
#
# Configures the the build settings for the specified Arduino Board.
#
#=============================================================================#
function(GET_AVR_FLAGS COMPILE_FLAGS_VAR BOARD_ID LIBS FOR_LIBRARY)
    set(BOARD_CORE ${${BOARD_ID}.build.core})

    # Get Arduino version information
    if (ARDUINO_SDK_VERSION MATCHES "([0-9]+)[.]([0-9]+)")
        string(REPLACE "." "" ARDUINO_VERSION_DEFINE "${ARDUINO_SDK_VERSION}") # Normalize version (remove all periods)
        set(ARDUINO_VERSION_DEFINE "")
        if (CMAKE_MATCH_1 GREATER 0)
            set(ARDUINO_VERSION_DEFINE "${CMAKE_MATCH_1}")
        endif ()
        if (CMAKE_MATCH_2 GREATER 10)
            set(ARDUINO_VERSION_DEFINE "${ARDUINO_VERSION_DEFINE}${CMAKE_MATCH_2}")
        else ()
            set(ARDUINO_VERSION_DEFINE "${ARDUINO_VERSION_DEFINE}0${CMAKE_MATCH_2}")
        endif ()
    else ()
        message("Invalid Arduino SDK Version (${ARDUINO_SDK_VERSION})")
    endif ()

    # AVR flags
    list(APPEND COMPILE_FLAGS "-DF_CPU=${${BOARD_ID}.build.f_cpu} -DARDUINO=${ARDUINO_VERSION_DEFINE} -mmcu=${${BOARD_ID}.build.mcu}")
    if (DEFINED ${BOARD_ID}.build.vid)
        list(APPEND COMPILE_FLAGS "-DUSB_VID=${${BOARD_ID}.build.vid}")
    endif ()
    if (DEFINED ${BOARD_ID}.build.pid)
        list(APPEND COMPILE_FLAGS "-DUSB_PID=${${BOARD_ID}.build.pid}")
    endif ()
    if (ARDUINO_SDK_VERSION VERSION_GREATER 1.0 OR ARDUINO_SDK_VERSION VERSION_EQUAL 1.0)
        set(PIN_HEADER ${${${BOARD_ID}.build.variant}.path})
        if (PIN_HEADER)
            list(APPEND COMPILE_FLAGS "-I\"${PIN_HEADER}\"")
        endif ()
    endif ()

    # C include args
    get_property(INC_DIRS GLOBAL PROPERTY AVR_INCLUDE_DIRECTORIES)
    foreach (INC_DIR ${INC_DIRS})
        list(APPEND COMPILE_FLAGS "-I${INC_DIR}")
    endforeach ()

    if (APPLE)
        list(APPEND COMPILE_FLAGS "-I/Applications/Arduino.app/Contents/Java/hardware/tools/avr/avr/include/")
    endif ()

    # C link libraries
    if (NOT FOR_LIBRARY)
        list(APPEND COMPILE_FLAGS "-L${AVR_LIB_PATH}")
        if (NOT APPLE)
            list(APPEND LIBS "c" "m")
        endif ()
        foreach (LIB ${LIBS})
            list(APPEND COMPILE_FLAGS "-l${LIB}")
        endforeach ()
    endif ()

    # Build type flags
    if ("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
        list(APPEND COMPILE_FLAGS "${AVR_C_FLAGS_DEBUG}")
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
        list(APPEND COMPILE_FLAGS "${AVR_C_FLAGS_RELEASE}")
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
        list(APPEND COMPILE_FLAGS "${AVR_C_FLAGS_RELWITHDEBINFO}")
    elseif ("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
        list(APPEND COMPILE_FLAGS "${AVR_C_FLAGS_MINSIZEREL}")
    else () # None
        list(APPEND COMPILE_FLAGS "${AVR_C_FLAGS}")
    endif ()

    # Output
    separate_arguments(COMPILE_FLAGS)
    set(${COMPILE_FLAGS_VAR} "${COMPILE_FLAGS}" PARENT_SCOPE)
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_target(TARGET_NAME ALL_SRCS ALL_LIBS COMPILE_FLAGS LINK_FLAGS MANUAL)
#
#        TARGET_NAME - Target name
#        BOARD_ID    - Arduino board ID
#        ALL_SRCS    - All sources
#        ALL_LIBS    - All libraries
#        COMPILE_FLAGS - Compile flags
#        LINK_FLAGS    - Linker flags
#
# Creates an Arduino firmware target.
#
#=============================================================================#
function(SETUP_AVR_TARGET TARGET_NAME BOARD_ID ALL_SRCS ALL_LIBS COMPILE_FLAGS LINK_FLAGS TEST_TARGET)

    add_custom_target(${TARGET_NAME} COMMAND ""
            COMMENT "Building AVR target: ${TARGET_NAME}")

    # Add lib dependencies
    foreach (LIB ${ALL_LIBS})
        add_dependencies(${TARGET_NAME} "${LIB}-avr")
    endforeach ()

    get_avr_flags(COMPILE_FLAGS "${BOARD_ID}" "${ALL_LIBS}" False)
    set(TARGET_PATH ${CMAKE_CURRENT_BINARY_DIR}/${TARGET_NAME})

    # Compile elf
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${AVR_C_COMPILER}
            ARGS ${ALL_SRCS}
            -o ${TARGET_PATH}.elf
            ${COMPILE_FLAGS}
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            COMMENT "Compiling ELF"
            VERBATIM)

    # Copy and translate object files
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${AVR_OBJCOPY}
            ${AVR_OBJCOPY_EEP_FLAGS}
            ${TARGET_PATH}.elf
            ${TARGET_PATH}.eep
            COMMENT "Generating EEP image"
            VERBATIM)

    # Convert firmware image to ASCII HEX format
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${AVR_OBJCOPY}
            ${AVR_OBJCOPY_HEX_FLAGS}
            ${TARGET_PATH}.elf
            ${TARGET_PATH}.hex
            COMMENT "Generating HEX image"
            VERBATIM)

    # Display target size
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND}
            -DFIRMWARE_IMAGE=${TARGET_PATH}.elf
            -DMCU=${${BOARD_ID}.build.mcu}
            -DEEPROM_IMAGE=${TARGET_PATH}.eep
            -P ${ARDUINO_SIZE_SCRIPT}
            COMMENT "Calculating image size"
            VERBATIM)

    # Create ${TARGET_NAME}-size target
    if (SIZE_TARGETS)
        add_custom_target(${TARGET_NAME}-size
                COMMAND ${CMAKE_COMMAND}
                -DFIRMWARE_IMAGE=${TARGET_PATH}.elf
                -DMCU=${${BOARD_ID}.build.mcu}
                -DEEPROM_IMAGE=${TARGET_PATH}.eep
                -P ${ARDUINO_SIZE_SCRIPT}
                DEPENDS ${TARGET_NAME}
                COMMENT "Calculating ${TARGET_NAME} image size")
    endif ()

    # Save define and path to global variable
    if (TEST_TARGET)
        string(TOUPPER ${TARGET_NAME} TARGET_NAME)
        string(REPLACE "-" "_" TARGET_NAME ${TARGET_NAME})
        get_property(DEFINES GLOBAL PROPERTY TEST_FIRMWARE_DEFINES)
        get_property(PATHS GLOBAL PROPERTY TEST_FIRMWARE_PATHS)
        list(APPEND DEFINES ${TARGET_NAME})
        list(APPEND PATHS ${TARGET_PATH}.elf)

        set_property(GLOBAL PROPERTY TEST_FIRMWARE_DEFINES ${DEFINES})
        set_property(GLOBAL PROPERTY TEST_FIRMWARE_PATHS ${PATHS})
    endif ()
endfunction()

#=============================================================================#
# [PUBLIC/USER]
# see documentation at top
#=============================================================================#
function(REGISTER_HARDWARE_PLATFORM PLATFORM_PATH)
    string(REGEX REPLACE "/$" "" PLATFORM_PATH ${PLATFORM_PATH})
    GET_FILENAME_COMPONENT(PLATFORM ${PLATFORM_PATH} NAME)

    if (PLATFORM)
        string(TOUPPER ${PLATFORM} PLATFORM)
        list(FIND ARDUINO_PLATFORMS ${PLATFORM} platform_exists)

        if (platform_exists EQUAL -1)
            set(${PLATFORM}_PLATFORM_PATH ${PLATFORM_PATH} CACHE INTERNAL "The path to ${PLATFORM}")
            set(ARDUINO_PLATFORMS ${ARDUINO_PLATFORMS} ${PLATFORM} CACHE INTERNAL "A list of registered platforms")

            find_file(${PLATFORM}_CORES_PATH
                    NAMES cores
                    PATHS ${PLATFORM_PATH}
                    DOC "Path to directory containing the Arduino core sources.")

            find_file(${PLATFORM}_VARIANTS_PATH
                    NAMES variants
                    PATHS ${PLATFORM_PATH}
                    DOC "Path to directory containing the Arduino variant sources.")

            find_file(${PLATFORM}_BOOTLOADERS_PATH
                    NAMES bootloaders
                    PATHS ${PLATFORM_PATH}
                    DOC "Path to directory containing the Arduino bootloader images and sources.")

            find_file(${PLATFORM}_PROGRAMMERS_PATH
                    NAMES programmers.txt
                    PATHS ${PLATFORM_PATH}
                    DOC "Path to Arduino programmers definition file.")

            find_file(${PLATFORM}_BOARDS_PATH
                    NAMES boards.txt
                    PATHS ${PLATFORM_PATH}
                    DOC "Path to Arduino boards definition file.")

            if (${PLATFORM}_BOARDS_PATH)
                load_arduino_style_settings(${PLATFORM}_BOARDS "${PLATFORM_PATH}/boards.txt")
            endif ()

            if (${PLATFORM}_PROGRAMMERS_PATH)
                load_arduino_style_settings(${PLATFORM}_PROGRAMMERS "${ARDUINO_PROGRAMMERS_PATH}")
            endif ()

            if (${PLATFORM}_VARIANTS_PATH)
                file(GLOB sub-dir ${${PLATFORM}_VARIANTS_PATH}/*)
                foreach (dir ${sub-dir})
                    if (IS_DIRECTORY ${dir})
                        get_filename_component(variant ${dir} NAME)
                        set(VARIANTS ${VARIANTS} ${variant} CACHE INTERNAL "A list of registered variant boards")
                        set(${variant}.path ${dir} CACHE INTERNAL "The path to the variant ${variant}")
                    endif ()
                endforeach ()
            endif ()

            if (${PLATFORM}_CORES_PATH)
                file(GLOB sub-dir ${${PLATFORM}_CORES_PATH}/*)
                foreach (dir ${sub-dir})
                    if (IS_DIRECTORY ${dir})
                        get_filename_component(core ${dir} NAME)
                        set(CORES ${CORES} ${core} CACHE INTERNAL "A list of registered cores")
                        set(${core}.path ${dir} CACHE INTERNAL "The path to the core ${core}")
                    endif ()
                endforeach ()
            endif ()
        endif ()
    endif ()

endfunction()

#=============================================================================#
#                        Internal Functions
#=============================================================================#

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# parse_generator_arguments(TARGET_NAME PREFIX OPTIONS ARGS MULTI_ARGS [ARG1 ARG2 .. ARGN])
#
#         PREFIX     - Parsed options prefix
#         OPTIONS    - List of options
#         ARGS       - List of one value keyword arguments
#         MULTI_ARGS - List of multi value keyword arguments
#         [ARG1 ARG2 .. ARGN] - command arguments [optional]
#
# Parses generator options from either variables or command arguments
#
#=============================================================================#
macro(PARSE_GENERATOR_ARGUMENTS TARGET_NAME PREFIX OPTIONS ARGS MULTI_ARGS)
    cmake_parse_arguments(${PREFIX} "${OPTIONS}" "${ARGS}" "${MULTI_ARGS}" ${ARGN})
    error_for_unparsed(${PREFIX})
    load_generator_settings(${TARGET_NAME} ${PREFIX} ${OPTIONS} ${ARGS} ${MULTI_ARGS})

    # WORKAROUND: Store options in variable OPTION_ARGS to pass it to function calls
    foreach (OPTION ${OPTIONS})
        if (${${PREFIX}_${OPTION}})
            if (NOT DEFINED OPTION_ARGS)
                set(OPTION_ARGS ${OPTION})
            else ()
                set(OPTION_ARGS ${OPTION_ARGS} ${OPTION})
            endif ()
        endif ()
    endforeach ()
endmacro()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# load_generator_settings(TARGET_NAME PREFIX [SUFFIX_1 SUFFIX_2 .. SUFFIX_N])
#
#         TARGET_NAME - The base name of the user settings
#         PREFIX      - The prefix name used for generator settings
#         SUFFIX_XX   - List of suffixes to load
#
#  Loads a list of user settings into the generators scope. User settings have
#  the following syntax:
#
#      ${BASE_NAME}${SUFFIX}
#
#  The BASE_NAME is the target name and the suffix is a specific generator settings.
#
#  For every user setting found a generator setting is created of the follwoing fromat:
#
#      ${PREFIX}${SUFFIX}
#
#  The purpose of loading the settings into the generator is to not modify user settings
#  and to have a generic naming of the settings within the generator.
#
#=============================================================================#
function(LOAD_GENERATOR_SETTINGS TARGET_NAME PREFIX)
    foreach (GEN_SUFFIX ${ARGN})
        if (${TARGET_NAME}_${GEN_SUFFIX} AND NOT ${PREFIX}_${GEN_SUFFIX})
            set(${PREFIX}_${GEN_SUFFIX} ${${TARGET_NAME}_${GEN_SUFFIX}} PARENT_SCOPE)
        endif ()
    endforeach ()
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_upload(BOARD_ID TARGET_NAME PORT)
#
#        BOARD_ID    - Arduino board id
#        TARGET_NAME - Target name
#        PORT        - Serial port for upload
#        PROGRAMMER_ID - Programmer ID
#        AVRDUDE_FLAGS - avrdude flags
#
# Create an upload target (${TARGET_NAME}-upload) for the specified Arduino target.
#
#=============================================================================#
function(setup_arduino_upload BOARD_ID TARGET_NAME PORT PROGRAMMER_ID AVRDUDE_FLAGS)
    setup_arduino_bootloader_upload(${TARGET_NAME} ${BOARD_ID} ${PORT} "${AVRDUDE_FLAGS}")

    # Add programmer support if defined
    if (PROGRAMMER_ID AND ${PROGRAMMER_ID}.protocol)
        setup_arduino_programmer_burn(${TARGET_NAME} ${BOARD_ID} ${PROGRAMMER_ID} ${PORT} "${AVRDUDE_FLAGS}")
        SETUP_ARDUINO_BOOTLOADER_BURN(${TARGET_NAME} ${BOARD_ID} ${PROGRAMMER_ID} ${PORT} "${AVRDUDE_FLAGS}")
    endif ()
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_bootloader_upload(TARGET_NAME BOARD_ID PORT)
#
#      TARGET_NAME - target name
#      BOARD_ID    - board id
#      PORT        - serial port
#      AVRDUDE_FLAGS - avrdude flags (override)
#
# Set up target for upload firmware via the bootloader.
#
# The target for uploading the firmware is ${TARGET_NAME}-upload .
#
#=============================================================================#
function(setup_arduino_bootloader_upload TARGET_NAME BOARD_ID PORT AVRDUDE_FLAGS)
    set(UPLOAD_TARGET ${TARGET_NAME}-upload)
    set(AVRDUDE_ARGS)

    setup_arduino_bootloader_args(${BOARD_ID} ${TARGET_NAME} ${PORT} "${AVRDUDE_FLAGS}" AVRDUDE_ARGS)

    if (NOT AVRDUDE_ARGS)
        message("Could not generate default avrdude bootloader args, aborting!")
        return()
    endif ()

    if (NOT EXECUTABLE_OUTPUT_PATH)
        set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
    endif ()
    set(TARGET_PATH ${EXECUTABLE_OUTPUT_PATH}/${TARGET_NAME})

    list(APPEND AVRDUDE_ARGS "-Uflash:w:${TARGET_PATH}.hex")
    list(APPEND AVRDUDE_ARGS "-Ueeprom:w:${TARGET_PATH}.eep:i")
    add_custom_target(${UPLOAD_TARGET}
            ${AVRDUDE_PROGRAM}
            ${AVRDUDE_ARGS}
            DEPENDS ${TARGET_NAME})

    # Global upload target
    if (NOT TARGET upload)
        add_custom_target(upload)
    endif ()

    add_dependencies(upload ${UPLOAD_TARGET})
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_programmer_burn(TARGET_NAME BOARD_ID PROGRAMMER PORT AVRDUDE_FLAGS)
#
#      TARGET_NAME - name of target to burn
#      BOARD_ID    - board id
#      PROGRAMMER  - programmer id
#      PORT        - serial port
#      AVRDUDE_FLAGS - avrdude flags (override)
# 
# Sets up target for burning firmware via a programmer.
#
# The target for burning the firmware is ${TARGET_NAME}-burn .
#
#=============================================================================#
function(setup_arduino_programmer_burn TARGET_NAME BOARD_ID PROGRAMMER PORT AVRDUDE_FLAGS)
    set(PROGRAMMER_TARGET ${TARGET_NAME}-burn)

    set(AVRDUDE_ARGS)

    setup_arduino_programmer_args(${BOARD_ID} ${PROGRAMMER} ${TARGET_NAME} ${PORT} "${AVRDUDE_FLAGS}" AVRDUDE_ARGS)

    if (NOT AVRDUDE_ARGS)
        message("Could not generate default avrdude programmer args, aborting!")
        return()
    endif ()

    if (NOT EXECUTABLE_OUTPUT_PATH)
        set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR})
    endif ()
    set(TARGET_PATH ${EXECUTABLE_OUTPUT_PATH}/${TARGET_NAME})

    list(APPEND AVRDUDE_ARGS "-Uflash:w:${TARGET_PATH}.hex")

    add_custom_target(${PROGRAMMER_TARGET}
            ${AVRDUDE_PROGRAM}
            ${AVRDUDE_ARGS}
            DEPENDS ${TARGET_NAME})
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_bootloader_burn(TARGET_NAME BOARD_ID PROGRAMMER PORT AVRDUDE_FLAGS)
# 
#      TARGET_NAME - name of target to burn
#      BOARD_ID    - board id
#      PROGRAMMER  - programmer id
#      PORT        - serial port
#      AVRDUDE_FLAGS - avrdude flags (override)
#
# Create a target for burning a bootloader via a programmer.
#
# The target for burning the bootloader is ${TARGET_NAME}-burn-bootloader
#
#=============================================================================#
function(SETUP_ARDUINO_BOOTLOADER_BURN TARGET_NAME BOARD_ID PROGRAMMER PORT AVRDUDE_FLAGS)
    set(BOOTLOADER_TARGET ${TARGET_NAME}-burn-bootloader)

    set(AVRDUDE_ARGS)

    setup_arduino_programmer_args(${BOARD_ID} ${PROGRAMMER} ${TARGET_NAME} ${PORT} "${AVRDUDE_FLAGS}" AVRDUDE_ARGS)

    if (NOT AVRDUDE_ARGS)
        message("Could not generate default avrdude programmer args, aborting!")
        return()
    endif ()

    foreach (ITEM unlock_bits high_fuses low_fuses path file)
        if (NOT ${BOARD_ID}.bootloader.${ITEM})
            message("Missing ${BOARD_ID}.bootloader.${ITEM}, not creating bootloader burn target ${BOOTLOADER_TARGET}.")
            return()
        endif ()
    endforeach ()

    if (NOT EXISTS "${ARDUINO_BOOTLOADERS_PATH}/${${BOARD_ID}.bootloader.path}/${${BOARD_ID}.bootloader.file}")
        message("${ARDUINO_BOOTLOADERS_PATH}/${${BOARD_ID}.bootloader.path}/${${BOARD_ID}.bootloader.file}")
        message("Missing bootloader image, not creating bootloader burn target ${BOOTLOADER_TARGET}.")
        return()
    endif ()

    # Erase the chip
    list(APPEND AVRDUDE_ARGS "-e")

    # Set unlock bits and fuses (because chip is going to be erased)
    list(APPEND AVRDUDE_ARGS "-Ulock:w:${${BOARD_ID}.bootloader.unlock_bits}:m")
    if (${BOARD_ID}.bootloader.extended_fuses)
        list(APPEND AVRDUDE_ARGS "-Uefuse:w:${${BOARD_ID}.bootloader.extended_fuses}:m")
    endif ()
    list(APPEND AVRDUDE_ARGS
            "-Uhfuse:w:${${BOARD_ID}.bootloader.high_fuses}:m"
            "-Ulfuse:w:${${BOARD_ID}.bootloader.low_fuses}:m")

    # Set bootloader image
    list(APPEND AVRDUDE_ARGS "-Uflash:w:${${BOARD_ID}.bootloader.file}:i")

    # Set lockbits
    list(APPEND AVRDUDE_ARGS "-Ulock:w:${${BOARD_ID}.bootloader.lock_bits}:m")

    # Create burn bootloader target
    add_custom_target(${BOOTLOADER_TARGET}
            ${AVRDUDE_PROGRAM} ${AVRDUDE_ARGS}
            WORKING_DIRECTORY ${ARDUINO_BOOTLOADERS_PATH}/${${BOARD_ID}.bootloader.path}
            DEPENDS ${TARGET_NAME})
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_programmer_args(BOARD_ID PROGRAMMER TARGET_NAME PORT AVRDUDE_FLAGS OUTPUT_VAR)
#
#      BOARD_ID    - board id
#      PROGRAMMER  - programmer id
#      TARGET_NAME - target name
#      PORT        - serial port
#      AVRDUDE_FLAGS - avrdude flags (override)
#      OUTPUT_VAR  - name of output variable for result
#
# Sets up default avrdude settings for burning firmware via a programmer.
#=============================================================================#
function(setup_arduino_programmer_args BOARD_ID PROGRAMMER TARGET_NAME PORT AVRDUDE_FLAGS OUTPUT_VAR)
    set(AVRDUDE_ARGS ${${OUTPUT_VAR}})

    if (NOT AVRDUDE_FLAGS)
        set(AVRDUDE_FLAGS ${ARDUINO_AVRDUDE_FLAGS})
        message(FATAL_ERROR "This should not happen")
    endif ()

    list(APPEND AVRDUDE_ARGS "-C${AVRDUDE_CONFIG_PATH}")

    #TODO: Check mandatory settings before continuing
    if (NOT ${PROGRAMMER}.protocol)
        message(FATAL_ERROR "Missing ${PROGRAMMER}.protocol, aborting!")
    endif ()

    list(APPEND AVRDUDE_ARGS "-c${${PROGRAMMER}.protocol}") # Set programmer

    if (${PROGRAMMER}.communication STREQUAL "usb")
        list(APPEND AVRDUDE_ARGS "-Pusb") # Set USB as port
    elseif (${PROGRAMMER}.communication STREQUAL "serial")
        list(APPEND AVRDUDE_ARGS "-P${PORT}") # Set port
        if (${PROGRAMMER}.speed)
            list(APPEND AVRDUDE_ARGS "-b${${PROGRAMMER}.speed}") # Set baud rate
        endif ()
    endif ()

    if (${PROGRAMMER}.force)
        list(APPEND AVRDUDE_ARGS "-F") # Set force
    endif ()

    if (${PROGRAMMER}.delay)
        list(APPEND AVRDUDE_ARGS "-i${${PROGRAMMER}.delay}") # Set delay
    endif ()

    list(APPEND AVRDUDE_ARGS "-p${${BOARD_ID}.build.mcu}")  # MCU Type

    list(APPEND AVRDUDE_ARGS ${AVRDUDE_FLAGS})

    set(${OUTPUT_VAR} ${AVRDUDE_ARGS} PARENT_SCOPE)
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_bootloader_args(BOARD_ID TARGET_NAME PORT AVRDUDE_FLAGS OUTPUT_VAR)
#
#      BOARD_ID    - board id
#      TARGET_NAME - target name
#      PORT        - serial port
#      AVRDUDE_FLAGS - avrdude flags (override)
#      OUTPUT_VAR  - name of output variable for result
#
# Sets up default avrdude settings for uploading firmware via the bootloader.
#=============================================================================#
function(setup_arduino_bootloader_args BOARD_ID TARGET_NAME PORT AVRDUDE_FLAGS OUTPUT_VAR)
    set(AVRDUDE_ARGS ${${OUTPUT_VAR}})

    if (NOT AVRDUDE_FLAGS)
        set(AVRDUDE_FLAGS ${ARDUINO_AVRDUDE_FLAGS})
    endif ()

    list(APPEND AVRDUDE_ARGS
            "-C${AVRDUDE_CONFIG_PATH}"  # avrdude config
            "-p${${BOARD_ID}.build.mcu}"        # MCU Type
            )

    # Programmer
    if (NOT ${BOARD_ID}.upload.protocol OR ${BOARD_ID}.upload.protocol STREQUAL "stk500")
        list(APPEND AVRDUDE_ARGS "-cstk500v1")
    else ()
        list(APPEND AVRDUDE_ARGS "-c${${BOARD_ID}.upload.protocol}")
    endif ()

    set(UPLOAD_SPEED "19200")
    if (${BOARD_ID}.upload.speed)
        set(UPLOAD_SPEED ${${BOARD_ID}.upload.speed})
    endif ()

    list(APPEND AVRDUDE_ARGS
            "-b${UPLOAD_SPEED}"     # Baud rate
            "-P${PORT}"                         # Serial port
            "-D"                                # Dont erase
            )

    list(APPEND AVRDUDE_ARGS ${AVRDUDE_FLAGS})

    set(${OUTPUT_VAR} ${AVRDUDE_ARGS} PARENT_SCOPE)
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# find_sources(VAR_NAME LIB_PATH RECURSE)
#
#        VAR_NAME - Variable name that will hold the detected sources
#        LIB_PATH - The base path
#        RECURSE  - Whether or not to recurse
#
# Finds all C/C++ sources located at the specified path.
#
#=============================================================================#
function(find_sources VAR_NAME LIB_PATH RECURSE)
    set(FILE_SEARCH_LIST
            ${LIB_PATH}/*.cpp
            ${LIB_PATH}/*.c
            ${LIB_PATH}/*.cc
            ${LIB_PATH}/*.cxx
            ${LIB_PATH}/*.h
            ${LIB_PATH}/*.hh
            ${LIB_PATH}/*.hxx)

    if (RECURSE)
        file(GLOB_RECURSE LIB_FILES ${FILE_SEARCH_LIST})
    else ()
        file(GLOB LIB_FILES ${FILE_SEARCH_LIST})
    endif ()

    if (LIB_FILES)
        set(${VAR_NAME} ${LIB_FILES} PARENT_SCOPE)
    endif ()
endfunction()

#=============================================================================#
# [PUBLIC]
#
# setup_serial_targets()
#
# Creates serial targets.
#
#=============================================================================#
function(SETUP_SERIAL_TARGETS)
    # Detect screen command
    if (CMAKE_HOST_UNIX)
        find_program(SCREEN screen)
        if (NOT SCREEN)
            message(FATAL_ERROR "Please install screen")
        endif ()
    else ()
        message(FATAL_ERROR "${CMAKE_HOST_SYSTEM_NAME} not supported yet!")
    endif ()

    # Detect terminal command
    file(GLOB TERMINALS "/usr/bin/gnome-terminal" "/usr/bin/konsole" "/usr/bin/xterm" "/opt/X11/bin/xterm")
    list(GET TERMINALS 0 TERMINAL)

    # Detect serial port
    if (CMAKE_HOST_SYSTEM_NAME STREQUAL "Linux")
        file(GLOB SERIAL_PORTS /dev/ttyACM*)
    elseif (CMAKE_HOST_SYSTEM_NAME STREQUAL "Darwin")
        file(GLOB SERIAL_PORTS /dev/cu.usbmodem*)
    else ()
        message(FATAL_ERROR "${CMAKE_HOST_SYSTEM_NAME} not supported yet.")
    endif ()

    # Create serial targets
    foreach (SERIAL_PORT ${SERIAL_PORTS})
        # Setup terminal arguments
        set(ARGUMENTS "-e" "'sh -c \"${SCREEN} -r || ${SCREEN} ${SERIAL_PORT}\"'")
        separate_arguments(ARGUMENTS)

        get_filename_component(SERIAL_NAME ${SERIAL_PORT} NAME)
        add_custom_target(serial-${SERIAL_NAME}
                COMMAND ${TERMINAL} ${ARGUMENTS})
    endforeach ()
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
# detect_arduino_version(VAR_NAME)
#
#       VAR_NAME - Variable name where the detected version will be saved
#
# Detects the Arduino SDK Version based on the revisions.txt file. The
# following variables will be generated:
#
#    ${VAR_NAME}         -> the full version (major.minor.patch)
#    ${VAR_NAME}_MAJOR   -> the major version
#    ${VAR_NAME}_MINOR   -> the minor version
#    ${VAR_NAME}_PATCH   -> the patch version
#
#=============================================================================#
function(detect_arduino_version VAR_NAME)
    if (ARDUINO_VERSION_PATH)
        file(READ ${ARDUINO_VERSION_PATH} RAW_VERSION)
        if ("${RAW_VERSION}" MATCHES " *[0]+([0-9]+)")
            set(PARSED_VERSION 0.${CMAKE_MATCH_1}.0)
        elseif ("${RAW_VERSION}" MATCHES "[ ]*([0-9]+[.][0-9]+[.][0-9]+)")
            set(PARSED_VERSION ${CMAKE_MATCH_1})
        elseif ("${RAW_VERSION}" MATCHES "[ ]*([0-9]+[.][0-9]+)")
            set(PARSED_VERSION ${CMAKE_MATCH_1}.0)
        endif ()

        if (NOT PARSED_VERSION STREQUAL "")
            string(REPLACE "." ";" SPLIT_VERSION ${PARSED_VERSION})
            list(GET SPLIT_VERSION 0 SPLIT_VERSION_MAJOR)
            list(GET SPLIT_VERSION 1 SPLIT_VERSION_MINOR)
            list(GET SPLIT_VERSION 2 SPLIT_VERSION_PATCH)

            set(${VAR_NAME} "${PARSED_VERSION}" PARENT_SCOPE)
            set(${VAR_NAME}_MAJOR "${SPLIT_VERSION_MAJOR}" PARENT_SCOPE)
            set(${VAR_NAME}_MINOR "${SPLIT_VERSION_MINOR}" PARENT_SCOPE)
            set(${VAR_NAME}_PATCH "${SPLIT_VERSION_PATCH}" PARENT_SCOPE)
        endif ()
    endif ()
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
# load_arduino_style_settings(SETTINGS_LIST SETTINGS_PATH)
#
#      SETTINGS_LIST - Variable name of settings list
#      SETTINGS_PATH - File path of settings file to load.
#
# Load a Arduino style settings file into the cache.
# 
#  Examples of this type of settings file is the boards.txt and
# programmers.txt files located in ${ARDUINO_SDK}/hardware/arduino.
#
# Settings have to following format:
#
#      entry.setting[.subsetting] = value
#
# where [.subsetting] is optional
#
# For example, the following settings:
#
#      uno.name=Arduino Uno
#      uno.upload.protocol=stk500
#      uno.upload.maximum_size=32256
#      uno.build.mcu=atmega328p
#      uno.build.core=arduino
#
# will generate the follwoing equivalent CMake variables:
#
#      set(uno.name "Arduino Uno")
#      set(uno.upload.protocol     "stk500")
#      set(uno.upload.maximum_size "32256")
#      set(uno.build.mcu  "atmega328p")
#      set(uno.build.core "arduino")
#
#      set(uno.SETTINGS  name upload build)              # List of settings for uno
#      set(uno.upload.SUBSETTINGS protocol maximum_size) # List of sub-settings for uno.upload
#      set(uno.build.SUBSETTINGS mcu core)               # List of sub-settings for uno.build
# 
#  The ${ENTRY_NAME}.SETTINGS variable lists all settings for the entry, while
# ${ENTRY_NAME}.SUBSETTINGS variables lists all settings for a sub-setting of
# a entry setting pair.
#
#  These variables are generated in order to be able to  programatically traverse
# all settings (for a example see print_board_settings() function).
#
#=============================================================================#
function(LOAD_ARDUINO_STYLE_SETTINGS SETTINGS_LIST SETTINGS_PATH)

    if (NOT ${SETTINGS_LIST} AND EXISTS ${SETTINGS_PATH})
        file(STRINGS ${SETTINGS_PATH} FILE_ENTRIES)  # Settings file split into lines

        foreach (FILE_ENTRY ${FILE_ENTRIES})
            if ("${FILE_ENTRY}" MATCHES "^[^#]+=.*")
                string(REGEX MATCH "^[^=]+" SETTING_NAME ${FILE_ENTRY})
                string(REGEX MATCH "[^=]+$" SETTING_VALUE ${FILE_ENTRY})
                string(REPLACE "." ";" ENTRY_NAME_TOKENS ${SETTING_NAME})
                string(STRIP "${SETTING_VALUE}" SETTING_VALUE)

                list(LENGTH ENTRY_NAME_TOKENS ENTRY_NAME_TOKENS_LEN)

                # Add entry to settings list if it does not exist
                list(GET ENTRY_NAME_TOKENS 0 ENTRY_NAME)
                list(FIND ${SETTINGS_LIST} ${ENTRY_NAME} ENTRY_NAME_INDEX)
                if (ENTRY_NAME_INDEX LESS 0)
                    # Add entry to main list
                    list(APPEND ${SETTINGS_LIST} ${ENTRY_NAME})
                endif ()

                # Add entry setting to entry settings list if it does not exist
                set(ENTRY_SETTING_LIST ${ENTRY_NAME}.SETTINGS)
                list(GET ENTRY_NAME_TOKENS 1 ENTRY_SETTING)
                list(FIND ${ENTRY_SETTING_LIST} ${ENTRY_SETTING} ENTRY_SETTING_INDEX)
                if (ENTRY_SETTING_INDEX LESS 0)
                    # Add setting to entry
                    list(APPEND ${ENTRY_SETTING_LIST} ${ENTRY_SETTING})
                    set(${ENTRY_SETTING_LIST} ${${ENTRY_SETTING_LIST}}
                            CACHE INTERNAL "Arduino ${ENTRY_NAME} Board settings list")
                endif ()

                set(FULL_SETTING_NAME ${ENTRY_NAME}.${ENTRY_SETTING})

                # Add entry sub-setting to entry sub-settings list if it does not exists
                if (ENTRY_NAME_TOKENS_LEN GREATER 2)
                    set(ENTRY_SUBSETTING_LIST ${ENTRY_NAME}.${ENTRY_SETTING}.SUBSETTINGS)
                    list(GET ENTRY_NAME_TOKENS 2 ENTRY_SUBSETTING)
                    list(FIND ${ENTRY_SUBSETTING_LIST} ${ENTRY_SUBSETTING} ENTRY_SUBSETTING_INDEX)
                    if (ENTRY_SUBSETTING_INDEX LESS 0)
                        list(APPEND ${ENTRY_SUBSETTING_LIST} ${ENTRY_SUBSETTING})
                        set(${ENTRY_SUBSETTING_LIST} ${${ENTRY_SUBSETTING_LIST}}
                                CACHE INTERNAL "Arduino ${ENTRY_NAME} Board sub-settings list")
                    endif ()
                    set(FULL_SETTING_NAME ${FULL_SETTING_NAME}.${ENTRY_SUBSETTING})
                endif ()

                # Save setting value
                set(${FULL_SETTING_NAME} ${SETTING_VALUE}
                        CACHE INTERNAL "Arduino ${ENTRY_NAME} Board setting")


            endif ()
        endforeach ()
        set(${SETTINGS_LIST} ${${SETTINGS_LIST}}
                CACHE STRING "List of detected Arduino Board configurations")
        mark_as_advanced(${SETTINGS_LIST})
    endif ()
endfunction()

#=============================================================================#
# print_settings(ENTRY_NAME)
#
#      ENTRY_NAME - name of entry
#
# Print the entry settings (see load_arduino_syle_settings()).
#
#=============================================================================#
function(PRINT_SETTINGS ENTRY_NAME)
    if (${ENTRY_NAME}.SETTINGS)

        foreach (ENTRY_SETTING ${${ENTRY_NAME}.SETTINGS})
            if (${ENTRY_NAME}.${ENTRY_SETTING})
                message(STATUS "   ${ENTRY_NAME}.${ENTRY_SETTING}=${${ENTRY_NAME}.${ENTRY_SETTING}}")
            endif ()
            if (${ENTRY_NAME}.${ENTRY_SETTING}.SUBSETTINGS)
                foreach (ENTRY_SUBSETTING ${${ENTRY_NAME}.${ENTRY_SETTING}.SUBSETTINGS})
                    if (${ENTRY_NAME}.${ENTRY_SETTING}.${ENTRY_SUBSETTING})
                        message(STATUS "   ${ENTRY_NAME}.${ENTRY_SETTING}.${ENTRY_SUBSETTING}=${${ENTRY_NAME}.${ENTRY_SETTING}.${ENTRY_SUBSETTING}}")
                    endif ()
                endforeach ()
            endif ()
            message(STATUS "")
        endforeach ()
    endif ()
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# print_list(SETTINGS_LIST)
#
#      SETTINGS_LIST - Variables name of settings list
#
# Print list settings and names (see load_arduino_syle_settings()).
#=============================================================================#
function(PRINT_LIST SETTINGS_LIST)
    if (${SETTINGS_LIST})
        set(MAX_LENGTH 0)
        foreach (ENTRY_NAME ${${SETTINGS_LIST}})
            string(LENGTH "${ENTRY_NAME}" CURRENT_LENGTH)
            if (CURRENT_LENGTH GREATER MAX_LENGTH)
                set(MAX_LENGTH ${CURRENT_LENGTH})
            endif ()
        endforeach ()
        foreach (ENTRY_NAME ${${SETTINGS_LIST}})
            string(LENGTH "${ENTRY_NAME}" CURRENT_LENGTH)
            math(EXPR PADDING_LENGTH "${MAX_LENGTH}-${CURRENT_LENGTH}")
            set(PADDING "")
            foreach (X RANGE ${PADDING_LENGTH})
                set(PADDING "${PADDING} ")
            endforeach ()
            message(STATUS "   ${PADDING}${ENTRY_NAME}: ${${ENTRY_NAME}.name}")
        endforeach ()
    endif ()
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# setup_arduino_size_script(OUTPUT_VAR)
#
#        OUTPUT_VAR - Output variable that will contain the script path
#
# Generates script used to display the firmware size.
#=============================================================================#
function(SETUP_ARDUINO_SIZE_SCRIPT OUTPUT_VAR)
    set(ARDUINO_SIZE_SCRIPT_PATH ${CMAKE_BINARY_DIR}/CMakeFiles/FirmwareSize.cmake)

    file(WRITE ${ARDUINO_SIZE_SCRIPT_PATH} "
        set(AVR_SIZE_PROGRAM ${AVR_SIZE_PROGRAM})
        set(AVR_SIZE_FLAGS -C --mcu=\${MCU})

        execute_process(COMMAND \${AVR_SIZE_PROGRAM} \${AVR_SIZE_FLAGS} \${FIRMWARE_IMAGE} \${EEPROM_IMAGE}
                        OUTPUT_VARIABLE SIZE_OUTPUT)


        string(STRIP \"\${SIZE_OUTPUT}\" RAW_SIZE_OUTPUT)

        # Convert lines into a list
        string(REPLACE \"\\n\" \";\" SIZE_OUTPUT_LIST \"\${SIZE_OUTPUT}\")

        set(SIZE_OUTPUT_LINES)
        foreach(LINE \${SIZE_OUTPUT_LIST})
            if(NOT \"\${LINE}\" STREQUAL \"\")
                list(APPEND SIZE_OUTPUT_LINES \"\${LINE}\")
            endif()
        endforeach()

        function(EXTRACT LIST_NAME INDEX VARIABLE)
            list(GET \"\${LIST_NAME}\" \${INDEX} RAW_VALUE)
            string(STRIP \"\${RAW_VALUE}\" VALUE)

            set(\${VARIABLE} \"\${VALUE}\" PARENT_SCOPE)
        endfunction()
        function(PARSE INPUT VARIABLE_PREFIX)
            if(\${INPUT} MATCHES \"([^:]+):[ \\t]*([0-9]+)[ \\t]*([^ \\t]+)[ \\t]*[(]([0-9.]+)%.*\")
                set(ENTRY_NAME      \${CMAKE_MATCH_1})
                set(ENTRY_SIZE      \${CMAKE_MATCH_2})
                set(ENTRY_SIZE_TYPE \${CMAKE_MATCH_3})
                set(ENTRY_PERCENT   \${CMAKE_MATCH_4})
            endif()

            set(\${VARIABLE_PREFIX}_NAME      \${ENTRY_NAME}      PARENT_SCOPE)
            set(\${VARIABLE_PREFIX}_SIZE      \${ENTRY_SIZE}      PARENT_SCOPE)
            set(\${VARIABLE_PREFIX}_SIZE_TYPE \${ENTRY_SIZE_TYPE} PARENT_SCOPE)
            set(\${VARIABLE_PREFIX}_PERCENT   \${ENTRY_PERCENT}   PARENT_SCOPE)
        endfunction()

        list(LENGTH SIZE_OUTPUT_LINES SIZE_OUTPUT_LENGTH)
        #message(\"\${SIZE_OUTPUT_LINES}\")
        #message(\"\${SIZE_OUTPUT_LENGTH}\")
        if (\${SIZE_OUTPUT_LENGTH} STREQUAL 14)
            EXTRACT(SIZE_OUTPUT_LINES 3 FIRMWARE_PROGRAM_SIZE_ROW)
            EXTRACT(SIZE_OUTPUT_LINES 5 FIRMWARE_DATA_SIZE_ROW)
            PARSE(FIRMWARE_PROGRAM_SIZE_ROW FIRMWARE_PROGRAM)
            PARSE(FIRMWARE_DATA_SIZE_ROW  FIRMWARE_DATA)

            set(FIRMWARE_STATUS \"Firmware Size: \")
            set(FIRMWARE_STATUS \"\${FIRMWARE_STATUS} [\${FIRMWARE_PROGRAM_NAME}: \${FIRMWARE_PROGRAM_SIZE} \${FIRMWARE_PROGRAM_SIZE_TYPE} (\${FIRMWARE_PROGRAM_PERCENT}%)] \")
            set(FIRMWARE_STATUS \"\${FIRMWARE_STATUS} [\${FIRMWARE_DATA_NAME}: \${FIRMWARE_DATA_SIZE} \${FIRMWARE_DATA_SIZE_TYPE} (\${FIRMWARE_DATA_PERCENT}%)]\")
            set(FIRMWARE_STATUS \"\${FIRMWARE_STATUS} on \${MCU}\")

            EXTRACT(SIZE_OUTPUT_LINES 10 EEPROM_PROGRAM_SIZE_ROW)
            EXTRACT(SIZE_OUTPUT_LINES 12 EEPROM_DATA_SIZE_ROW)
            PARSE(EEPROM_PROGRAM_SIZE_ROW EEPROM_PROGRAM)
            PARSE(EEPROM_DATA_SIZE_ROW  EEPROM_DATA)

            set(EEPROM_STATUS \"EEPROM   Size: \")
            set(EEPROM_STATUS \"\${EEPROM_STATUS} [\${EEPROM_PROGRAM_NAME}: \${EEPROM_PROGRAM_SIZE} \${EEPROM_PROGRAM_SIZE_TYPE} (\${EEPROM_PROGRAM_PERCENT}%)] \")
            set(EEPROM_STATUS \"\${EEPROM_STATUS} [\${EEPROM_DATA_NAME}: \${EEPROM_DATA_SIZE} \${EEPROM_DATA_SIZE_TYPE} (\${EEPROM_DATA_PERCENT}%)]\")
            set(EEPROM_STATUS \"\${EEPROM_STATUS} on \${MCU}\")

            message(\"\${FIRMWARE_STATUS}\")
            message(\"\${EEPROM_STATUS}\\n\")

            if(\$ENV{VERBOSE})
                message(\"\${RAW_SIZE_OUTPUT}\\n\")
            elseif(\$ENV{VERBOSE_SIZE})
                message(\"\${RAW_SIZE_OUTPUT}\\n\")
            endif()
        else()
            message(\"\${RAW_SIZE_OUTPUT}\")
        endif()
    ")

    set(${OUTPUT_VAR} ${ARDUINO_SIZE_SCRIPT_PATH} PARENT_SCOPE)
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
#  arduino_debug_on()
#
# Enables Arduino module debugging.
#=============================================================================#
function(ARDUINO_DEBUG_ON)
    set(ARDUINO_DEBUG True PARENT_SCOPE)
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
#  arduino_debug_off()
#
# Disables Arduino module debugging.
#=============================================================================#
function(ARDUINO_DEBUG_OFF)
    set(ARDUINO_DEBUG False PARENT_SCOPE)
endfunction()


#=============================================================================#
# [PRIVATE/INTERNAL]
#
# arduino_debug_msg(MSG)
#
#        MSG - Message to print
#
# Print Arduino debugging information. In order to enable printing
# use arduino_debug_on() and to disable use arduino_debug_off().
#=============================================================================#
function(ARDUINO_DEBUG_MSG MSG)
    if (ARDUINO_DEBUG)
        message("## ${MSG}")
    endif ()
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# remove_comments(SRC_VAR OUT_VAR)
#
#        SRC_VAR - variable holding sources
#        OUT_VAR - variable holding sources with no comments
#
# Removes all comments from the source code.
#=============================================================================#
function(REMOVE_COMMENTS SRC_VAR OUT_VAR)
    string(REGEX REPLACE "[\\./\\\\]" "_" FILE "${NAME}")

    set(SRC ${${SRC_VAR}})

    #message(STATUS "removing comments from: ${FILE}")
    #file(WRITE "${CMAKE_BINARY_DIR}/${FILE}_pre_remove_comments.txt" ${SRC})
    #message(STATUS "\n${SRC}")

    # remove all comments
    string(REGEX REPLACE "([/][/][^\n]*)|([/][\\*]([^\\*]|([\\*]+[^/\\*]))*[\\*]+[/])" "" OUT "${SRC}")

    #file(WRITE "${CMAKE_BINARY_DIR}/${FILE}_post_remove_comments.txt" ${SRC})
    #message(STATUS "\n${SRC}")

    set(${OUT_VAR} ${OUT} PARENT_SCOPE)

endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# get_num_lines(DOCUMENT OUTPUT_VAR)
#
#        DOCUMENT   - Document contents
#        OUTPUT_VAR - Variable which will hold the line number count
#
# Counts the line number of the document.
#=============================================================================#
function(GET_NUM_LINES DOCUMENT OUTPUT_VAR)
    string(REGEX MATCHALL "[\n]" MATCH_LIST "${DOCUMENT}")
    list(LENGTH MATCH_LIST NUM)
    set(${OUTPUT_VAR} ${NUM} PARENT_SCOPE)
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# required_variables(MSG msg VARS var1 var2 .. varN)
#
#        MSG  - Message to be displayed in case of error
#        VARS - List of variables names to check
#
# Ensure the specified variables are not empty, otherwise a fatal error is emmited.
#=============================================================================#
function(REQUIRED_VARIABLES)
    cmake_parse_arguments(INPUT "" "MSG" "VARS" ${ARGN})
    error_for_unparsed(INPUT)
    foreach (VAR ${INPUT_VARS})
        if ("${${VAR}}" STREQUAL "")
            message(FATAL_ERROR "${VAR} not set: ${INPUT_MSG}")
        endif ()
    endforeach ()
endfunction()

#=============================================================================#
# [PRIVATE/INTERNAL]
#
# error_for_unparsed(PREFIX)
#
#        PREFIX - Prefix name
#
# Emit fatal error if there are unparsed argument from cmake_parse_arguments().
#=============================================================================#
function(ERROR_FOR_UNPARSED PREFIX)
    set(ARGS "${${PREFIX}_UNPARSED_ARGUMENTS}")
    if (NOT ("${ARGS}" STREQUAL ""))
        message(FATAL_ERROR "unparsed argument: ${ARGS}")
    endif ()
endfunction()


#=============================================================================#
#                         System Paths                                        #
#=============================================================================#
if (UNIX)
    include(Platform/UnixPaths)
    if (APPLE)
        list(APPEND CMAKE_SYSTEM_PREFIX_PATH ~/Applications
                /Applications
                /Developer/Applications
                /sw        # Fink
                /opt/local) # MacPorts
    endif ()
elseif (WIN32)
    include(Platform/WindowsPaths)
endif ()


#=============================================================================#
#                         Detect Arduino SDK                                  #
#=============================================================================#
if (NOT ARDUINO_SDK_PATH)
    set(ARDUINO_PATHS)

    foreach (DETECT_VERSION_MAJOR 1)
        foreach (DETECT_VERSION_MINOR RANGE 5 0)
            list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR})
            foreach (DETECT_VERSION_PATCH RANGE 3 0)
                list(APPEND ARDUINO_PATHS arduino-${DETECT_VERSION_MAJOR}.${DETECT_VERSION_MINOR}.${DETECT_VERSION_PATCH})
            endforeach ()
        endforeach ()
    endforeach ()

    foreach (VERSION RANGE 23 19)
        list(APPEND ARDUINO_PATHS arduino-00${VERSION})
    endforeach ()

    if (UNIX)
        file(GLOB SDK_PATH_HINTS /usr/share/arduino*
                /opt/local/arduino*
                /opt/arduino*
                /usr/local/share/arduino*)
    elseif (WIN32)
        set(SDK_PATH_HINTS "C:\\Program Files\\Arduino"
                "C:\\Program Files (x86)\\Arduino"
                )
    endif ()
    list(SORT SDK_PATH_HINTS)
    list(REVERSE SDK_PATH_HINTS)
endif ()

find_path(ARDUINO_SDK_PATH
        NAMES lib/version.txt
        PATH_SUFFIXES share/arduino
        Arduino.app/Contents/Resources/Java/
        Arduino.app/Contents/Java/
        ${ARDUINO_PATHS}
        HINTS ${SDK_PATH_HINTS}
        DOC "Arduino SDK path.")

if (ARDUINO_SDK_PATH)
    list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${ARDUINO_SDK_PATH}/hardware/tools/avr)
    list(APPEND CMAKE_SYSTEM_PREFIX_PATH ${ARDUINO_SDK_PATH}/hardware/tools/avr/utils)
else ()
    message(FATAL_ERROR "Could not find Arduino SDK (set ARDUINO_SDK_PATH)!")
endif ()


#=============================================================================#
#                        Commandline programs
#=============================================================================#
set(AVR_C_COMPILER "avr-gcc")
set(AVR_CXX_COMPILER "avr-g++")
set(AVR_OBJCOPY "avr-objcopy")
set(AVR_AR "avr-ar")

#=============================================================================#
#                              C Flags                                        
#=============================================================================#
set(AVR_C_FLAGS_COMMON "-mcall-prologues -ffunction-sections -fdata-sections -std=c11")
set(AVR_C_FLAGS "${AVR_C_FLAGS_COMMON} -Os -g" CACHE STRING "")
set(AVR_C_FLAGS_DEBUG "${AVR_C_FLAGS_COMMON} -Os -g" CACHE STRING "")
set(AVR_C_FLAGS_MINSIZEREL "${AVR_C_FLAGS_COMMON} -Os -DNDEBUG" CACHE STRING "")
set(AVR_C_FLAGS_RELEASE "${AVR_C_FLAGS_COMMON} -Os -DNDEBUG -w" CACHE STRING "")
set(AVR_C_FLAGS_RELWITHDEBINFO "${AVR_C_FLAGS_COMMON} -Os -g -w" CACHE STRING "")

#=============================================================================#
#                             C++ Flags                                       
#=============================================================================#
set(AVR_CXX_FLAGS_COMMON "${AVR_C_FLAGS_COMMON} -fno-exceptions")
set(AVR_CXX_FLAGS "${AVR_CXX_FLAGS_COMMON} -Os -g" CACHE STRING "")
set(AVR_CXX_FLAGS_DEBUG "${AVR_CXX_FLAGS_COMMON} -Os -g" CACHE STRING "")
set(AVR_CXX_FLAGS_MINSIZEREL "${AVR_CXX_FLAGS_COMMON} -Os -DNDEBUG" CACHE STRING "")
set(AVR_CXX_FLAGS_RELEASE "${AVR_CXX_FLAGS_COMMON} -Os -DNDEBUG" CACHE STRING "")
set(AVR_CXX_FLAGS_RELWITHDEBINFO "${AVR_CXX_FLAGS_COMMON} -Os -g" CACHE STRING "")

#=============================================================================#
#                       Executable Linker Flags                               #
#=============================================================================#
set(AVR_LINKER_FLAGS "-Wl,--gc-sections -lm")
set(AVR_EXE_LINKER_FLAGS "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_EXE_LINKER_FLAGS_DEBUG "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_EXE_LINKER_FLAGS_MINSIZEREL "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_EXE_LINKER_FLAGS_RELEASE "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_EXE_LINKER_FLAGS_RELWITHDEBINFO "${AVR_LINKER_FLAGS}" CACHE STRING "")

#=============================================================================#
#                       Shared Lbrary Linker Flags                            #
#=============================================================================#
set(AVR_SHARED_LINKER_FLAGS "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_SHARED_LINKER_FLAGS_DEBUG "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_SHARED_LINKER_FLAGS_MINSIZEREL "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_SHARED_LINKER_FLAGS_RELEASE "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_SHARED_LINKER_FLAGS_RELWITHDEBINFO "${AVR_LINKER_FLAGS}" CACHE STRING "")

set(AVR_MODULE_LINKER_FLAGS "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_MODULE_LINKER_FLAGS_DEBUG "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_MODULE_LINKER_FLAGS_MINSIZEREL "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_MODULE_LINKER_FLAGS_RELEASE "${AVR_LINKER_FLAGS}" CACHE STRING "")
set(AVR_MODULE_LINKER_FLAGS_RELWITHDEBINFO "${AVR_LINKER_FLAGS}" CACHE STRING "")

#=============================================================================#
#                         Avr flags Settings
#=============================================================================#
set(AVR_OBJCOPY_EEP_FLAGS -O ihex -j .eeprom --set-section-flags=.eeprom=alloc,load --no-change-warnings --change-section-lma .eeprom=0 CACHE STRING "")
set(AVR_OBJCOPY_HEX_FLAGS -O ihex -R .eeprom CACHE STRING "")
set(AVRDUDE_FLAGS -V CACHE STRING "")
set(AVR_LIB_PATH ${CMAKE_BINARY_DIR}/avr-lib/ CACHE STRING "")
file(MAKE_DIRECTORY ${AVR_LIB_PATH})

#=============================================================================#
#                          Initialization                                     
#=============================================================================#
if (NOT ARDUINO_FOUND AND ARDUINO_SDK_PATH)
    register_hardware_platform(${ARDUINO_SDK_PATH}/hardware/arduino/)
    register_hardware_platform(${ARDUINO_SDK_PATH}/hardware/arduino/avr)

    find_file(ARDUINO_LIBRARIES_PATH_DEF
            NAMES libraries
            PATHS ${ARDUINO_SDK_PATH}
            DOC "Path to directory containing the Arduino (default) libraries.")

    find_file(ARDUINO_LIBRARIES_PATH_PLATFORM
            NAMES libraries
            PATHS ${ARDUINO_SDK_PATH}/hardware/arduino/avr/
            DOC "Path to directory containing the Arduino (plateform specific) libraries.")

    set(ARDUINO_LIBRARIES_PATH "${ARDUINO_LIBRARIES_PATH_DEF};${ARDUINO_LIBRARIES_PATH_PLATFORM}"
            CACHE STRING "Path to directory containing the Arduino (default) libraries.")


    find_file(ARDUINO_VERSION_PATH
            NAMES lib/version.txt
            PATHS ${ARDUINO_SDK_PATH}
            DOC "Path to Arduino version file.")

    find_program(AVRDUDE_PROGRAM
            NAMES avrdude
            PATHS ${ARDUINO_SDK_PATH}
            PATH_SUFFIXES hardware/tools hardware/tools/avr/bin
            NO_DEFAULT_PATH)

    find_program(AVRDUDE_PROGRAM
            NAMES avrdude
            DOC "Path to avrdude programmer binary.")

    find_file(AVRDUDE_CONFIG_PATH
            NAMES avrdude.conf
            PATHS ${ARDUINO_SDK_PATH} /etc/avrdude /etc
            PATH_SUFFIXES hardware/tools
            hardware/tools/avr/etc
            DOC "Path to avrdude programmer configuration file.")

    find_program(AVR_OBJCOPY_PROGRAM
            avr-objcopy)

    find_program(AVR_SIZE_PROGRAM
            NAMES avr-size)

    set(ARDUINO_DEFAULT_BOARD uno CACHE STRING "Default Arduino Board ID when not specified.")
    set(ARDUINO_DEFAULT_PORT CACHE STRING "Default Arduino port when not specified.")
    set(ARDUINO_DEFAULT_SERIAL CACHE STRING "Default Arduino Serial command when not specified.")
    set(ARDUINO_DEFAULT_PROGRAMMER CACHE STRING "Default Arduino Programmer ID when not specified.")

    # Ensure that all required paths are found
    required_variables(VARS
            ARDUINO_PLATFORMS
            ARDUINO_CORES_PATH
            ARDUINO_BOOTLOADERS_PATH
            ARDUINO_LIBRARIES_PATH
            ARDUINO_BOARDS_PATH
            ARDUINO_PROGRAMMERS_PATH
            ARDUINO_VERSION_PATH
            AVRDUDE_PROGRAM
            AVRDUDE_FLAGS
            AVRDUDE_CONFIG_PATH
            AVR_OBJCOPY_PROGRAM
            AVR_SIZE_PROGRAM
            MSG "Invalid Arduino SDK path (${ARDUINO_SDK_PATH}).\n")

    detect_arduino_version(ARDUINO_SDK_VERSION)
    set(ARDUINO_SDK_VERSION ${ARDUINO_SDK_VERSION} CACHE STRING "Arduino SDK Version")
    set(ARDUINO_SDK_VERSION_MAJOR ${ARDUINO_SDK_VERSION_MAJOR} CACHE STRING "Arduino SDK Major Version")
    set(ARDUINO_SDK_VERSION_MINOR ${ARDUINO_SDK_VERSION_MINOR} CACHE STRING "Arduino SDK Minor Version")
    set(ARDUINO_SDK_VERSION_PATCH ${ARDUINO_SDK_VERSION_PATCH} CACHE STRING "Arduino SDK Patch Version")

    if (ARDUINO_SDK_VERSION VERSION_LESS 0.19)
        message(FATAL_ERROR "Unsupported Arduino SDK (require verion 0.19 or higher)")
    endif ()

    message(STATUS "Arduino SDK version ${ARDUINO_SDK_VERSION}: ${ARDUINO_SDK_PATH}")

    setup_arduino_size_script(ARDUINO_SIZE_SCRIPT)
    set(ARDUINO_SIZE_SCRIPT ${ARDUINO_SIZE_SCRIPT} CACHE INTERNAL "Arduino Size Script")

    set(ARDUINO_FOUND True CACHE INTERNAL "Arduino Found")
    mark_as_advanced(
            ARDUINO_CORES_PATH
            ARDUINO_VARIANTS_PATH
            ARDUINO_BOOTLOADERS_PATH
            ARDUINO_LIBRARIES_PATH
            ARDUINO_BOARDS_PATH
            ARDUINO_PROGRAMMERS_PATH
            ARDUINO_VERSION_PATH
            AVRDUDE_CONFIG_PATH
            AVRDUDE_FLAGS
            AVRDUDE_PROGRAM
            AVR_OBJCOPY_EEP_FLAGS
            AVR_OBJCOPY_HEX_FLAGS
            AVR_SIZE_PROGRAM)
endif ()

