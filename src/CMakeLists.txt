generate_arduino_firmware(main
        BOARD uno
        SRCS main.c
        LIBS datafusion fc io ir kalman log math sonar)
