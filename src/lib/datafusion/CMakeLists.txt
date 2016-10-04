generate_arduino_library(datafusion
    BOARD uno
	SRCS datafusion.c
	HDRS ../datafusion.h
	LIBS io
	NO_AUTOLIBS)
