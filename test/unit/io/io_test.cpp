#include <sim_avr.h>
#include "io_test.h"

void IOTest::SetPinMode_Pin0SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN0_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin7SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN7_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin8SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN8_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin13SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN13_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin0SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN0_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin7SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN7_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x80));
}

void IOTest::SetPinMode_Pin8SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN8_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin13SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN13_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x20));
}

void SetPinMode_Pin13SetHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::WritePin_Pin0WriteLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', DDRD_, PIN0, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin7WriteLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', DDRD_, PIN7, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin8WriteLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN0, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin13WriteLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN5, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin0WriteHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', DDRD_, PIN0, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x01));
}

void IOTest::WritePin_Pin7WriteHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', DDRD_, PIN7, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x80));
}

void IOTest::WritePin_Pin8WriteHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN0, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x01));
}

void IOTest::WritePin_Pin13WriteHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN5, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x20));
}

void WritePin_Pin13WriteHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN5, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::ReadPin_Pin0ReadLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', PORTD_, PIN0, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin7ReadLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', PORTD_, PIN7, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin8ReadLOW_ExpectLOW() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', PORTB_, PIN0, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin13ReadLOW_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', PORTB_, PIN5, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin0ReadHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', PORTD_, PIN0, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin7ReadHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'D', PORTD_, PIN7, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin8ReadHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', PORTB_, PIN0, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

void IOTest::ReadPin_Pin13ReadHIGH_ExpectHIGH() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', PORTB_, PIN5, LOW);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(avr->state != cpu_Stopped));
}

