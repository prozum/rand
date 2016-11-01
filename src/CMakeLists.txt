add_subdirectory(lib)

generate_avr_firmware(main
        BOARD uno
        SRCS main.c
        LIBS io fc ir kalman log sonar)
