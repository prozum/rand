#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11")

#set(SOURCE_FILES etellerandet.c drone_bits_to_image/drone_bits_to_image.c drone_bits_to_image/drone_bits_to_image.h ../../src/lib/map/map.c ../../src/lib/map/map.h)
set(SOURCE_FILES main.c)
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)
add_executable(bits_to_pbm ${SOURCE_FILES})
target_link_libraries(bits_to_pbm core map)
