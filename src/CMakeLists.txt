add_subdirectory(lib)

generate_avr_firmware(main
        BOARD uno
        SRCS main.c
        MOCK
        LIBS io datafusion fc ir kalman log sonar)
