generate_avr_library(positioning
    BOARD uno
    SRCS positioning.c
    HDRS positioning.h
    LIBS kalman
)