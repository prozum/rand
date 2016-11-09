# Add mock definitions
add_definitions(-DMOCK)
add_definitions(-D__AVR_ATmega328P__)

add_executable(tests main.cpp
        io/io_test.cpp
        sonar/sonar_test.cpp
        kalman/kalman_test.cpp
        log/log_test.cpp
        matrix/matrix_test.cpp
)
target_link_libraries(tests common core sonar kalman ${CPPUNIT_LIBRARIES})
