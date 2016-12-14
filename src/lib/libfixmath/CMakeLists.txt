generate_avr_library(libfixmath
    MOCK
    BOARD uno
	SRCS fix16.c fix16_exp.c fix16_trig.c fix16_sqrt.c
	LIBS )
