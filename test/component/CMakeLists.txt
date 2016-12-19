# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

# Load defines with paths for firmwares compile in test_firmware
load_test_firmware_defines()

add_executable(component-tests Main.cpp
        io/IOTest.cpp
        )

add_test_dependencies(component-tests)

target_link_libraries(component-tests common core ${CPPUNIT_LIBRARIES})