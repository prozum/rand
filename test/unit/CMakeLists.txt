# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

# Load defines with paths for firmwares compile in test_firmware
load_test_firmware_defines()

add_executable(unit-tests main.cpp
        io/io_test.cpp
        sonar/sonar_test.cpp
        kalman/kalman_test.cpp
        log/log_test.cpp
        matrix/matrix_test.cpp
)
target_link_libraries(unit-tests common core sonar kalman ${CPPUNIT_LIBRARIES})
add_test_dependencies(unit-tests)
