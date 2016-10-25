set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

set(ARDUINO_C_FLAGS "-g -Os -ffunction-sections -fdata-sections")

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
    add_subdirectory(test)
endif()
