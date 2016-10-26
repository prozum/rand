set(PIN_IDS 0 7 8 13)

foreach(PIN_ID ${PIN_IDS})
	# INPUT/OUTPUT tests
	foreach(PIN_MODE "INPUT;OUTPUT")
		configure_file(setpinmode.c.in setpinmode.c)
		generate_test_firmware(pin${PIN_ID}-${PIN_MODE} setpinmode.c)
	endforeach()

	# HIGH/LOW tests
	foreach(PIN_VAL "HIGH;LOW")
		configure_file(digitalread.c.in digitalread.c)
		generate_test_firmware(pin${PIN_ID}-${PIN_VAL} digitalread.c)

		configure_file(digitalwrite.c.in digitalwrite.c)
		generate_test_firmware(pin${PIN_ID}-${PIN_VAL} digitalwrite.c)
	endforeach()
endforeach()
