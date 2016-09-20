generate_arduino_library(gdb_support
    BOARD uno
	SRCS avr8-stub.c
	HDRS avr8-stub.h
	NO_AUTOLIBS)
