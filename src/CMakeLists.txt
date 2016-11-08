add_subdirectory(lib)

generate_avr_firmware(main
        BOARD uno
        SRCS main.c
        LIBS core fc ir kalman sonar)
