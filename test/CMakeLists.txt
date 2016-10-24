# Build firmwares
add_subdirectory(unit_firmware)

# Build native unit test system
cmake_minimum_required(VERSION 2.8)
PROJECT(tests CXX)

# Overwrite Arduino toolchain
set(CMAKE_CXX_COMPILER_FORCED TRUE)
set(CMAKE_C_COMPILER /usr/bin/cc)
set(CMAKE_CXX_COMPILER /usr/bin/c++)
set(CMAKE_C _FLAGS "")
set(CMAKE_CXX_FLAGS "")
set(CMAKE_CXX_FLAGS_DEBUG "")
set(CMAKE_CXX_FLAGS_MINSIZEREL "")
set(CMAKE_CXX_FLAGS_RELEASE "")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "")

find_package(PkgConfig)
pkg_search_module(CPPUNIT cppunit)

include_directories(common simavr simavr/avr)

add_subdirectory(simavr)

add_subdirectory(common)
add_subdirectory(unit)
add_subdirectory(component)
add_subdirectory(system)
