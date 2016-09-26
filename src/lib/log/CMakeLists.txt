generate_arduino_library(log
    BOARD uno
	SRCS log.c
	HDRS log.h
	LIBS io
	NO_AUTOLIBS)
