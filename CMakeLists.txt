set(CMAKE_TOOLCHAIN_FILE cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(ArduinoExample C CXX)

print_board_list()
print_programmer_list()

include_directories(src/gdb-support)

add_subdirectory(src)
add_subdirectory(samples)
