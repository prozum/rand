cmake_minimum_required(VERSION 2.8)
include(cmake/Arduino.cmake)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project(rand C CXX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Options
option(SAMPLES "Samples" OFF)
option(TESTS "Tests" ON)
option(SERIAL_TARGETS "Serial Targets" OFF)
option(SIZE_TARGETS "Size Targets" OFF)

include_directories(src src/lib)
avr_include_directories(src src/lib)

add_subdirectory(src)

message("compiler: ${CMAKE_CXX_COMPILER_ID}")

if (SERIAL_TARGETS)
    setup_serial_targets()
endif ()

if (SAMPLES)
    add_subdirectory(samples)
endif ()

if (TESTS)
    add_subdirectory(test)
endif ()
