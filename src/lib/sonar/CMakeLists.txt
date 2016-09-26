generate_arduino_library(sonar
    BOARD uno
	SRCS sonar.c
	HDRS sonar.h
	LIBS io
	NO_AUTOLIBS)
