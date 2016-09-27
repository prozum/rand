#include <io.h>

void io_set_pin(port_t port, uint8_t pin, pin_mode_t pm)
{
    switch (port) {
        case _PORTB:
            DDRB |= (pins.digital[pin]) * pm;
            break;
        case _PORTD:
            DDRD |= (pins.digital[pin+8] * pm);
            break;
        case _PORTC:
            /* todo */
            break;
        default:
            error++;
    }
}

void io_digital_write(port_t port, uint8_t pin, pin_state_t ps)
{
    switch (port) {
        case _PORTB:
            PORTB |= ps;
            break;
        case _PORTD:
            PORTD |= ps;
            break;
        default:
            error++;
    }
}

pin_state_t io_digital_read(port_t port, uint8_t pin)
{
    switch (port) {
        case _PORTB:
            return (pin_state_t)((PORTB & pins.digital[pin]) != 0);
        case _PORTD:
            return (pin_state_t)((PORTD & pins.digital[pin+8]) != 0);
        default:
            error++;
            return LOW;
    }
}

uint16_t io_analog_read(uint8_t pin)
{

}