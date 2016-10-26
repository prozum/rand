generate_arduino_firmware(setpinmodeinput
		BOARD uno
		LIBS io
		SRCS setpinmodeinput.c)

generate_arduino_firmware(setpinmodeoutput
		BOARD uno
		LIBS io
		SRCS setpinmodeoutput.c)

generate_arduino_firmware(digitalwritelow
		BOARD uno
		LIBS io
		SRCS digitalwritelow.c)

generate_arduino_firmware(digitawritehigh
		BOARD uno
		LIBS io
		SRCS digitalwritehigh.c)

generate_arduino_firmware(digitalreadlow
		BOARD uno
		LIBS io
		SRCS digitalreadlow.c)

generate_arduino_firmware(digitalreadhigh
		BOARD uno
		LIBS io
		SRCS digitalreadhigh.c)