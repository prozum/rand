get_property(IO_TEST_FIRMWARE_PATHS GLOBAL PROPERTY IO_TEST_FIRMWARE_PATHS)
get_property(IO_TEST_FIRMWARE_DEFINES GLOBAL PROPERTY IO_TEST_FIRMWARE_DEFINES)

list(LENGTH IO_TEST_FIRMWARE_PATHS LENGTH)
math(EXPR LENGTH "${LENGTH} - 1" )
foreach(ITER RANGE ${LENGTH})
    list(GET IO_TEST_FIRMWARE_PATHS ${ITER} PATH)
    list(GET IO_TEST_FIRMWARE_DEFINES ${ITER} DEFINE)
    add_definitions(-D${DEFINE}=\"${PATH}\")
endforeach()

add_library(iotest io_test.cpp io_test.h)
target_link_libraries(simavr)