#include "tools.h"

avr_t* Tools::init(const char *fname, uint32_t freq) {
    avr_t *avr = NULL;
    elf_firmware_t f;

    avr = avr_make_mcu_by_name("atmega328p");

    elf_read_firmware(fname, &f);

    avr_init(avr);
    avr_load_firmware(avr, &f);

    return avr;
}

void Tools::avr_step(avr_t *avr, uint32_t steps) {
    for (int i = 0; i < steps; ++i) {
        avr_run(avr);
    }
}

avr_ioport_state_t Tools::avr_get_state(avr_t *avr, char port) {
    avr_ioport_state_t state;
    avr_ioctl(avr, AVR_IOCTL_IOPORT_GETSTATE(port), &state);

    return state;
}

void Tools::avr_set_state(avr_t *avr, char port, int reg, int mask, int v) {
    avr_ioport_external_t ext;
    ext.name = reg;
    ext.value = v;
    ext.mask = mask;
    avr_ioctl(avr, AVR_IOCTL_IOPORT_SET_EXTERNAL(port), &ext);
}