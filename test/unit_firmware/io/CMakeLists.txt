set(PIN_IDS 0 7 8 13)

get_property(IO_TEST_FIRMWARE_PATHS GLOBAL PROPERTY IO_TEST_FIRMWARE_PATHS)
get_property(IO_TEST_FIRMWARE_DEFINES GLOBAL PROPERTY IO_TEST_FIRMWARE_DEFINES)

foreach(PIN_ID ${PIN_IDS})
    set(PIN "PIN${PIN_ID}")

    set(PIN_MODE "INPUT")
    configure_file(setpinmode.c.in setpinmode.c)
    generate_test_firmware(pin${PIN_ID}-input setpinmode.c)
    set(FIRMWARE_DEFINE "TEST_FIRMWARE_PIN${PIN_ID}_INPUT")
    list(APPEND IO_TEST_FIRMWARE_DEFINES ${FIRMWARE_DEFINE})
    list(APPEND IO_TEST_FIRMWARE_PATHS ${${FIRMWARE_DEFINE}})

    set(PIN_MODE "OUTPUT")
    configure_file(setpinmode.c.in setpinmode.c)
    generate_test_firmware(pin${PIN_ID}-output setpinmode.c)
    set(FIRMWARE_DEFINE "TEST_FIRMWARE_PIN${PIN_ID}_OUTPUT")
    list(APPEND IO_TEST_FIRMWARE_DEFINES ${FIRMWARE_DEFINE})
    list(APPEND IO_TEST_FIRMWARE_PATHS ${${FIRMWARE_DEFINE}})
endforeach()

set_property(GLOBAL PROPERTY IO_TEST_FIRMWARE_PATHS ${IO_TEST_FIRMWARE_PATHS})
set_property(GLOBAL PROPERTY IO_TEST_FIRMWARE_DEFINES ${IO_TEST_FIRMWARE_DEFINES})
