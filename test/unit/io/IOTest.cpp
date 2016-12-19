#include "IOTest.h"
#include <sim/sim_avr.h>

CPPUNIT_TEST_SUITE_REGISTRATION(IOTest);

void IOTest::SetPinMode_Pin0SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN0_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::SetPinMode_Pin7SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN7_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::SetPinMode_Pin8SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN8_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::SetPinMode_Pin13SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN13_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::SetPinMode_Pin0SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN0_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x01, (int)state.ddr);
}

void IOTest::SetPinMode_Pin7SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN7_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x80, (int)state.ddr);
}

void IOTest::SetPinMode_Pin8SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN8_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x01, (int)state.ddr);
}

void IOTest::SetPinMode_Pin13SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN13_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x20, (int)state.ddr);
}

void IOTest::SetPinMode_Pin13SetHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::SetPinMode_Pin13SetLessThan0_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.ddr);
}

void IOTest::WritePin_Pin0WriteLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN0_DWRITE_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRD_, PIN0, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.port);
}

void IOTest::WritePin_Pin7WriteLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN7_DWRITE_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRD_, PIN7, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.port);
}

void IOTest::WritePin_Pin8WriteLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN8_DWRITE_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN0, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.pin);
}

void IOTest::WritePin_Pin13WriteLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN13_DWRITE_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN5, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.port);
}

void IOTest::WritePin_Pin0WriteHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN0_DWRITE_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRD_, PIN0, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x01, (int)state.port);
}

void IOTest::WritePin_Pin7WriteHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN7_DWRITE_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRD_, PIN7, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x80, (int)state.port);
}

void IOTest::WritePin_Pin8WriteHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN8_DWRITE_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN0, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x01, (int)state.port);
}

void IOTest::WritePin_Pin13WriteHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN13_DWRITE_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN5, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x20, (int)state.port);
}

void IOTest::WritePin_Pin13WriteHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN5, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.port);
}

void IOTest::WritePin_Pin13WriteLessThan0_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRB_, PIN5, OUTPUT);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, 0x00, (int)state.port);
}

void IOTest::ReadPin_Pin0ReadLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN0_DREAD_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTD_, PIN0, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin7ReadLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN7_DREAD_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTD_, PIN7, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin8ReadLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN8_DREAD_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTB_, PIN0, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin13ReadLOW_ExpectLOW() {
    char const *fname = TEST_FW_PIN13_DREAD_LOW;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTB_, PIN5, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin0ReadHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN0_DREAD_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, DDRD_, PIN0, INPUT);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin7ReadHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN7_DREAD_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTD_, PIN7, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin8ReadHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN8_DREAD_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTB_, PIN0, HIGH);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}

void IOTest::ReadPin_Pin13ReadHIGH_ExpectHIGH() {
    char const *fname = TEST_FW_PIN13_DREAD_HIGH;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_set_state(avr, PORTB_, PIN5, LOW);
    Tools::avr_step(avr, STEPS);

    CPPUNIT_ASSERT_EQUAL_MESSAGE(INVALID_DDR, (int)0xCFFF, (int)avr->opcode);
}
