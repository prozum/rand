#include "IOTest.h"
#include <sim/sim_avr.h>

CPPUNIT_TEST_SUITE_REGISTRATION(IOTest);

void IOTest::SetPinMode_Pin0AndPin7SetOUT_ExpectBothOUT() {
    char const *fname = TEST_FW_PIN0AND7_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x81, (int)state.ddr);
}