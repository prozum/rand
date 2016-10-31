file(GLOB SRCS
        "*.c"
        "*.h")
add_library(simavr-cores ${SRCS})
target_link_libraries(simavr-cores simavr)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    include_directories(simavr-cores /usr/lib/avr/include)
else()
    message(FATAL_ERROR "Tests not supported on host OS")
endif()
