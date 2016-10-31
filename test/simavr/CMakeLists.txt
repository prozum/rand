add_subdirectory(cores)

find_package(LibElf REQUIRED)
if (NOT LIBELF_FOUND)
    message(FATAL_ERROR "Please install libelf")
endif()

include_directories(${LIBELF_INCLUDE_DIRS})
include_directories(/usr/local/include/)
include_directories(avr)

file(GLOB SRCS
        "sim/*.c"
        "sim/*.h")

add_library(simavr ${SRCS})
target_link_libraries(simavr simavr-cores ${LIBELF_LIBRARIES})
#set_target_properties(simavr PROPERTIES LINKER_LANGUAGE C)
