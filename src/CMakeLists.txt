add_subdirectory(lib)

generate_arduino_firmware(main
        BOARD uno
        SRCS main.c
        LIBS io datafusion fc ir kalman log sonar)
