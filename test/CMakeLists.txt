cmake_minimum_required(VERSION 2.8)

PROJECT(tests C CXX)

set(CMAKE_CXX_COMPILER_FORCED TRUE)

find_package(PkgConfig)
pkg_search_module(CPPUNIT cppunit)

set(CMAKE_CXX_COMPILER gcc)
set(CMAKE_CXX_FLAGS "-lcppunit")

include_directories(../src/lib/ ../src/lib/io)
include_directories(simavr simavr/avr)
include_directories(common)

add_subdirectory(common)
add_subdirectory(simavr)
add_subdirectory(unit)
add_subdirectory(component)
add_subdirectory(system)
