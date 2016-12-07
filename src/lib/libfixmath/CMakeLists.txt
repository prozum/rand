add_definitions(-DFIXMATH_OPTIMIZE_8BIT)

generate_avr_library(libfixmath
    MOCK
    BOARD uno
	SRCS fix16.c fix16_exp.c fix16_trig.c
	LIBS )
