add_subdirectory(lib)

generate_avr_firmware(main
        BOARD uno
        SRCS main.c task.c
        LIBS core fc sonar laser ir nav search kalman matrix map libfixmath)
