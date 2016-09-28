#include <io.h>

void io_set_pin(port_t port, uint8_t pin, pin_mode_t pm)
{
    switch (port) {
        case _PORTB:
            DDRB |= (pins.portb_out[pin] * pm);
            break;
        case _PORTD:
            DDRD |= (pins.portd_out[pin] * pm);
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
            return (pin_state_t)((PINB & pins.portb_in[pin]));
        case _PORTD:
            return (pin_state_t)((PIND & pins.portd_in[pin]));
        default:
            error++;
            return LOW;
    }
}

void io_analog_init(uint8_t pin)
{
    ADMUX = pin;
    ADMUX |= (1 << REFS0);

    ADCSRA |= (1 << ADATE);

    ADCSRB = 0;

    ADCSRA |= (1 << ADEN);

    ADCSRA |= (1 << ADSC);
}

uint16_t io_analog_read(uint8_t pin)
{

}