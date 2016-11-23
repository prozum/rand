generate_avr_library(positioning
        MOCK
    BOARD uno
    SRCS positioning.c
    LIBS fc kalman core
)