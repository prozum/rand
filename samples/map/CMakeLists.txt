#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

#set(SOURCE_FILES etellerandet.c drone_bits_to_image/drone_bits_to_image.c drone_bits_to_image/drone_bits_to_image.h ../../src/lib/map/map.c ../../src/lib/map/map.h)
#set(SOURCE_FILES main.c)
#add_definitions(-DMOCK)
#add_definitions(-D__AVR_ATmega328P__)
#add_executable(map ${SOURCE_FILES})
#target_link_libraries(map core map)

generate_avr_firmware(map-sample
        BOARD uno
        LIBS core map
        SRCS main.c)
