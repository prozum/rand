generate_arduino_library(kalman
        BOARD uno
        SRCS kalman.c
        HDRS ../kalman.h
        LIBS io
        NO_AUTOLIBS)
