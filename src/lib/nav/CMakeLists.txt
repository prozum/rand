generate_avr_library(nav
        MOCK
    BOARD uno
    SRCS nav.c
    LIBS fc kalman core map
)