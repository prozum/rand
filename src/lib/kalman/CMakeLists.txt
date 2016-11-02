generate_avr_library(kalman
        MOCK
        BOARD uno
        SRCS kalman_datafusion.c kalman.c
        LIBS core)
