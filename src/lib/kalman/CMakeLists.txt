generate_avr_library(kalman
        BOARD uno
        SRCS kalman.c single_kalman.c
        LIBS io)
