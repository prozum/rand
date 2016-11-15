generate_avr_library(sonar
        MOCK
        BOARD uno
        SRCS sonar.c
        LIBS core kalman)
