#include <io.h>

void set_pin_mode(dpin_t pin, pin_mode_t pm)
{
    uint8_t port_ = dports[pin];
    uint8_t pin_  = pins[pin];

    switch (port_) {
        case PINB_:
            DDRB |= (pin_ * pm);
            break;
        case PIND_:
            DDRD |= (pin_ * pm);
            break;
        default:
            error++;
    }
}

void digital_write(dpin_t pin, pin_state_t ps)
{
    uint8_t port_ = dports[pin];
    uint8_t pin_  = pins[pin];

    switch (port_) {
        case PINB_:
            PORTB |= (pin_ * ps);
            break;
        case PIND_:
            PORTD |= (pin_ * ps);
            break;
        default:
            error++;
    }
}

pin_state_t digital_read(dpin_t pin)
{
    uint8_t port_ = dports[pin];
    uint8_t pin_  = pins[pin];

    switch (port_) {
        case PINB_:
            return (pin_state_t)(PINB & pin_);
        case PIND_:
            return (pin_state_t)(PIND & pin_);
        default:
            error++;
    }
}

/*

void analog_init(uint8_t pin)
{
    ADMUX = pin;
    ADMUX |= (1 << REFS0);

    ADCSRA |= (1 << ADATE);

    ADCSRB = 0;

    ADCSRA |= (1 << ADEN);

    ADCSRA |= (1 << ADSC);
}

uint16_t analog_read(uint8_t pin)
{

}
 */