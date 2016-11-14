add_subdirectory(lib)

generate_avr_firmware(main
        BOARD uno
        SRCS main.c task.h
        LIBS core fc)
