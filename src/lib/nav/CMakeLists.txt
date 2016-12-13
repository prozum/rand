generate_avr_library(nav
        MOCK
    BOARD uno
    SRCS nav.c
    LIBS fc kalman map search core
)