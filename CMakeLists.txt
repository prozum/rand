cmake_minimum_required(VERSION 2.8)
include(cmake/Arduino.cmake)
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

project(rand C CXX)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# Options
option(SAMPLES "Samples" OFF)
option(TESTS "Tests" OFF)
option(SIMULATOR "Simulator" OFF)
option(DOC "Documentation" OFF)
option(SERIAL_TARGETS "Serial Targets" OFF)
option(SIZE_TARGETS "Size Targets" OFF)

include_directories(src src/lib)
avr_include_directories(src src/lib)

add_subdirectory(src)

if (SAMPLES)
    add_subdirectory(samples)
endif ()

if (TESTS)
    add_subdirectory(test)
endif ()

if (SIMULATOR)
    add_subdirectory(test/randsim)
endif ()

if (DOC)
	include(cmake/Doxygen.cmake)
endif()	

if (SERIAL_TARGETS)
    setup_serial_targets()
endif ()
