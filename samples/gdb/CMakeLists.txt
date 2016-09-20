generate_arduino_firmware(gdb
	BOARD uno
	SRCS main.c
	LIBS gdb_support
	PORT /dev/ttyACM0)
