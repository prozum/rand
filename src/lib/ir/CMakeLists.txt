generate_arduino_library(ir
    BOARD uno
	SRCS ir.c
	HDRS ../ir.h
	LIBS io
	NO_AUTOLIBS)
