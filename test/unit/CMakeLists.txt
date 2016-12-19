# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

# Load defines with paths for firmwares compile in test_firmware
load_test_firmware_defines()

add_executable(unit-tests Main.cpp
        io/IOTest.cpp
        sonar/SonarTest.cpp
        kalman/KalmanTest.cpp
        kalman/KalmanDatafusionTest.cpp
        log/LogTest.cpp
        matrix/MatrixTest.cpp
        nav/NavTest.cpp
        )

add_test_dependencies(unit-tests)

target_link_libraries(unit-tests common core sonar kalman matrix laser libfixmath nav ${CPPUNIT_LIBRARIES})
