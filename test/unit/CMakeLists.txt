load_test_firmware_defines()
add_executable(tests main.cpp io/io_test.cpp log/log_test.cpp)

target_link_libraries(tests common ${CPPUNIT_LIBRARIES})
