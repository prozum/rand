generate_arduino_library(io
    BOARD uno
	SRCS io.c
	HDRS ../io.h
		LIBS log
	NO_AUTOLIBS)
