add_executable(tests main.cpp io/io_test.cpp kalman/kalman_test.cpp)

target_link_libraries(tests common ${CPPUNIT_LIBRARIES})
