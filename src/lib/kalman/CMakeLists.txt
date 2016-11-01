generate_avr_library(kalman
        BOARD uno
        SRCS kalman_datafusion.c kalman.c
        LIBS io)
