cmake_minimum_required(VERSION 2.8)
PROJECT(tests C CXX)

# Include cmake modules
SET(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../cmake" ${CMAKE_MODULE_PATH})

# CppSharp
find_package(PkgConfig)
pkg_search_module(CPPUNIT cppunit)
if(NOT CPPUNIT_FOUND)
	message(FATAL_ERROR "Please install CppUnit development files")
endif()

# Load test firmware defines
list(LENGTH TEST_FIRMWARE_DEFINES LENGTH)
math(EXPR LENGTH "${LENGTH} - 1")
foreach(ITER RANGE ${LENGTH})
	list(GET TEST_FIRMWARE_DEFINES ${ITER} DEFINE)
	list(GET TEST_FIRMWARE_PATHS ${ITER} PATH)
	add_definitions(-D${DEFINE}=\"${PATH}\")
endforeach()

# Includes
include_directories(common simavr simavr/cores simavr/sim simavr/sim/avr)

add_subdirectory(simavr)
add_subdirectory(common)
add_subdirectory(unit)
add_subdirectory(component)
add_subdirectory(system)
