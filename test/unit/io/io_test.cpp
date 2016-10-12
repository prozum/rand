#include "io_test.h"

void IOTest::SetPinMode_Pin0SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin1SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin2SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin3SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin4SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin5SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin6SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin7SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin8SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin9SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin10SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin11SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin12SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin13SetIN_ExpectIN() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x00));
}

void IOTest::SetPinMode_Pin0SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin1SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x02));
}

void IOTest::SetPinMode_Pin2SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x04));
}

void IOTest::SetPinMode_Pin3SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x08));
}

void IOTest::SetPinMode_Pin4SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x10));
}

void IOTest::SetPinMode_Pin5SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x20));
}

void IOTest::SetPinMode_Pin6SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x40));
}

void IOTest::SetPinMode_Pin7SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x80));
}

void IOTest::SetPinMode_Pin8SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x01));
}

void IOTest::SetPinMode_Pin9SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x02));
}

void IOTest::SetPinMode_Pin10SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x04));
}

void IOTest::SetPinMode_Pin11SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x08));
}

void IOTest::SetPinMode_Pin12SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x10));
}

void IOTest::SetPinMode_Pin13SetOUT_ExpectOUT() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'B');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.ddr != 0x20));
}

void IOTest::WritePin_Pin0WriteLOW_ExpectLOW() {
    char *fname = "";

    avr_t *avr = Tools::avr_init(fname, F_CPU);
    Tools::avr_step(avr, STEPS);

    avr_ioport_state_t state = Tools::avr_get_state(avr, 'D');

    CPPUNIT_ASSERT_ASSERTION_FAIL_MESSAGE(INVALID_DDR, CPPUNIT_ASSERT(state.port != 0x00));
}

void IOTest::WritePin_Pin1WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin2WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin3WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin4WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin5WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin6WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin7WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin8WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin9WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin10WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin11WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin12WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin13WriteLOW_ExpectLOW() {

}

void IOTest::WritePin_Pin0WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin1WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin2WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin3WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin4WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin5WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin6WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin7WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin8WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin9WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin10WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin11WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin12WriteHIGH_ExpectHIGH() {

}

void IOTest::WritePin_Pin13WriteHIGH_ExpectHIGH() {

}
