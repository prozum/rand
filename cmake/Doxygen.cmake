find_package(Doxygen)

if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Please install: doxygen and graphviz")
endif()

configure_file(cmake/Doxyfile.in Doxyfile @ONLY)

add_custom_target(doc ALL
    COMMAND ${DOXYGEN_EXECUTABLE} Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Doxygen"
    VERBATIM)

install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc/${CMAKE_PROJECT_NAME})
