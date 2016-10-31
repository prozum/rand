set(PIN_IDS 0 7 8 13)

foreach(PIN_ID ${PIN_IDS})
	# INPUT/OUTPUT tests
	foreach(PIN_MODE INPUT;OUTPUT)
		configure_file(setpinmode.c.in setpinmode.c)
 		generate_test_firmware(pin${PIN_ID}-pinmode-${PIN_MODE}
				               BOARD uno
				               SRCS setpinmode.c)
	endforeach()

	# HIGH/LOW tests
	foreach(PIN_VAL HIGH;LOW)
		configure_file(digitalread.c.in digitalread.c)
		generate_test_firmware(pin${PIN_ID}-dread-${PIN_VAL}
				               BOARD uno
							   SRCS digitalread.c)

		configure_file(digitalwrite.c.in digitalwrite.c)
		generate_test_firmware(pin${PIN_ID}-dwrite-${PIN_VAL}
							   BOARD uno
							   SRCS digitalwrite.c)
	endforeach()
endforeach()
