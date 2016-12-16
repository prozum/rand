generate_avr_library(kalman
        MOCK
        BOARD uno
        SRCS kalman-datafusion.c kalman.c
        LIBS core)
