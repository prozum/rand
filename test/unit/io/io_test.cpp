#include <sim_avr.h>
#include "io_test.h"

using namespace CppUnit;

Test *IOTest::suite() {
    TestSuite *suite = new TestSuite("IoTest");
    suite->addTest(setPinModeTests());
    suite->addTest(writePinTests());
    suite->addTest(readPinTests());

    return suite;
}

TestSuite *IOTest::setPinModeTests() {
    //Set pin mode
    TestSuite *spSuite = new TestSuite("SetPinMode");
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin0SetIn_ExpectIn", &IOTest::SetPinMode_Pin0SetIN_ExpectIN
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin7SetIn_ExpectIn", &IOTest::SetPinMode_Pin7SetIN_ExpectIN
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin8SetIn_ExpectIn", &IOTest::SetPinMode_Pin8SetIN_ExpectIN
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin13SetIn_ExpectIn", &IOTest::SetPinMode_Pin13SetIN_ExpectIN
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin0SetOut_ExpectOut", &IOTest::SetPinMode_Pin0SetOUT_ExpectOUT
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin7SetOut_ExpectOut", &IOTest::SetPinMode_Pin7SetOUT_ExpectOUT
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin8SetOut_ExpectOut", &IOTest::SetPinMode_Pin8SetOUT_ExpectOUT
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin13SetOut_ExpectOut", &IOTest::SetPinMode_Pin13SetOUT_ExpectOUT
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin13SetHigherThanOne_ExpectNoChange", &IOTest::SetPinMode_Pin13SetHigherThan1_ExpectNoChange
    ));
    spSuite->addTest(new TestCaller<IOTest>(
            "SetPinMode_Pin13SetLessThanZero_ExpectNoChange", &IOTest::SetPinMode_Pin13SetLessThan0_ExpectNoChange
    ));

    return spSuite;
}

TestSuite *IOTest::writePinTests() {
    TestSuite *wpSuite = new TestSuite("WritePin");

    wpSuite->addTest(new TestCaller<IOTest>(
       "_Pin0WriteLow_ExpectLow", &IOTest::WritePin_Pin0WriteLOW_ExpectLOW
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin0WriteHigh_ExpectHigh", &IOTest::WritePin_Pin0WriteHIGH_ExpectHIGH
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin7WriteHigh_ExpectHigh", &IOTest::WritePin_Pin7WriteHIGH_ExpectHIGH
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin7WriteLow_ExpectLow", &IOTest::WritePin_Pin7WriteLOW_ExpectLOW
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin8WriteLow_ExpectLow", &IOTest::WritePin_Pin8WriteLOW_ExpectLOW
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin8WriteHighExpectHigh", &IOTest::WritePin_Pin8WriteHIGH_ExpectHIGH
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin13WriteLowExpectLow", &IOTest::WritePin_Pin13WriteLOW_ExpectLOW
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin13WriteHighExpectHigh", &IOTest::WritePin_Pin13WriteHIGH_ExpectHIGH
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin13WriteLessThan0_ExpectNoChange", &IOTest::WritePin_Pin13WriteLessThan0_ExpectNoChange
    ));
    wpSuite->addTest(new TestCaller<IOTest>(
            "_Pin13WriteHigherThan1_ExpectNoChange", &IOTest::WritePin_Pin13WriteHigherThan1_ExpectNoChange
    ));
}

TestSuite *IOTest::readPinTests() {
    TestSuite *rpSuite = new TestSuite("ReadPin");

    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin0ReadLow_ExpectLow", &IOTest::ReadPin_Pin0ReadLOW_ExpectLOW
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin0ReadHighExpectHigh", &IOTest::ReadPin_Pin0ReadHIGH_ExpectHIGH
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin7ReadLow_ExpectLow", &IOTest::ReadPin_Pin7ReadLOW_ExpectLOW
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin7ReadHigh_ExpectHigh", &IOTest::ReadPin_Pin7ReadHIGH_ExpectHIGH
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin8ReadLow_ExpectLow", &IOTest::ReadPin_Pin8ReadLOW_ExpectLOW
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin8ReadHigh_ExpectHigh", &IOTest::ReadPin_Pin8ReadHIGH_ExpectHIGH
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin13_ReadLow_ExpectLow", &IOTest::ReadPin_Pin13ReadLOW_ExpectLOW
    ));
    rpSuite->addTest(new TestCaller<IOTest>(
            "Pin13_ReadHigh_ExpectHigh", &IOTest::ReadPin_Pin13ReadHIGH_ExpectHIGH
    ));

    return rpSuite;
}

void IOTest::SetPinMode_Pin0SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN0_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin7SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN7_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin8SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN8_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin13SetIN_ExpectIN() {
    char const *fname = TEST_FW_PIN13_PINMODE_INPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin0SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN0_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin7SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN7_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x80));
}

void IOTest::SetPinMode_Pin8SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN8_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin13SetOUT_ExpectOUT() {
    char const *fname = TEST_FW_PIN13_PINMODE_OUTPUT;

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x20));
}

void IOTest::SetPinMode_Pin13SetHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin13SetLessThan0_ExpectNoChange() {
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

void IOTest::WritePin_Pin13WriteHigherThan1_ExpectNoChange() {
    char const *fname = "";

    avr_t *avr = Tools::init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);
    Tools::avr_set_state(avr, 'B', DDRB_, PIN5, OUTPUT);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin13WriteLessThan0_ExpectNoChange() {
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

void IOTest::ReadPin_Pin13ReadLOW_ExpectLOW() {
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

