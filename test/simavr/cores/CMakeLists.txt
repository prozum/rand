file(GLOB SRCS
        "*.c"
        "*.h")
add_library(simavr-cores ${SRCS})
target_link_libraries(simavr-cores simavr)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux" OR MINGW)
    include_directories(simavr-cores /usr/lib/avr/include)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    include_directories(simavr-cores /Applications/Arduino.app/Contents/Java/hardware/tools/avr/avr/include/)
else()
    message(FATAL_ERROR "Tests not supported on host OS")
endif()
