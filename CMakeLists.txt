set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(rand C CXX)

# Options
option(SAMPLES "Samples" ON)
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