add_subdirectory(cores)

find_package(LibElf REQUIRED)
if (NOT LIBELF_FOUND)
    message(FATAL_ERROR "Please install libelf")
endif()

include_directories(${LIBELF_INCLUDE_DIRS} /usr/local/include/ avr)

file(GLOB SRCS
        "sim/*.c"
        "sim/*.h")

add_library(simavr ${SRCS})
set_property(TARGET simavr PROPERTY C_STANDARD 11)
target_link_libraries(simavr simavr-cores ${LIBELF_LIBRARIES})
