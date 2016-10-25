set(PIN_IDS 0 7 8 13)

foreach(PIN_ID ${PIN_IDS})
    set(PIN "PIN${PIN_ID}")

    set(PIN_MODE "INPUT")
    configure_file(setpinmode.c.in setpinmode.c)
    generate_test_firmware(pin${PIN_ID}-input setpinmode.c)

    set(PIN_MODE "OUTPUT")
    configure_file(setpinmode.c.in setpinmode.c)
    generate_test_firmware(pin${PIN_ID}-output setpinmode.c)
endforeach()
