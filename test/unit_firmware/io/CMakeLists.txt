set(PIN_IDS 0 7 8 13)

foreach(PIN_ID ${PIN_IDS})
	# INPUT/OUTPUT tests
	foreach(PIN_MODE INPUT;OUTPUT)
		configure_file(setpinmode.c.in pin${PIN_ID}-pinmode-${PIN_MODE}.c)
 		generate_avr_firmware(pin${PIN_ID}-pinmode-${PIN_MODE}
				               TEST
				               BOARD uno
				               LIBS core
				               SRCS pin${PIN_ID}-pinmode-${PIN_MODE}.c)
	endforeach()

	# HIGH/LOW tests
	foreach(PIN_VAL HIGH;LOW)
		configure_file(digitalread.c.in pin${PIN_ID}-dread-${PIN_VAL}.c)
		generate_avr_firmware(pin${PIN_ID}-dread-${PIN_VAL}
							   TEST
				               BOARD uno
				               LIBS core
							   SRCS pin${PIN_ID}-dread-${PIN_VAL}.c)

		configure_file(digitalwrite.c.in pin${PIN_ID}-dwrite-${PIN_VAL}.c)
		generate_avr_firmware(pin${PIN_ID}-dwrite-${PIN_VAL}
				               TEST
							   BOARD uno
				               LIBS core
							   SRCS pin${PIN_ID}-dwrite-${PIN_VAL}.c)
	endforeach()
endforeach()
