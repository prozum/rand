#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

set(SOURCE_FILES main.c)
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)
add_executable(map-sample ${SOURCE_FILES})
target_link_libraries(map-sample map core)

#generate_avr_firmware(map-sample
#        BOARD uno
#        LIBS core map
#        SRCS main.c)
