#include <io.h>

void set_pin_mode(dpin_t pin, pin_mode_t pm)
{
    // lookup the port value in dports
    uint8_t port_ = dports[pin];

    // loopup the pin value
    uint8_t pin_  = dpins[pin];

    switch (port_) {
        case PORTB_:
            DDRB |= (pin_ * pm);
            break;
        case PORTD_:
            DDRD |= (pin_ * pm);
            break;
        default:
            error++;
    }
}

void digital_write(dpin_t pin, dval_t ps)
{
    // lookup the port value based on a pin
    uint8_t port_ = dports[pin];

    // lookup the pin value based on a pin
    uint8_t pin_  = dpins[pin];

    // switch on the port looked up
    switch (port_) {
        case PORTB_: // if the
            PORTB |= (pin_ * ps);
            break;
        case PORTD_:
            PORTD |= (pin_ * ps);
            break;
        default:
            error++;
    }
}

dval_t digital_read(dpin_t pin)
{
    uint8_t port_ = dports[pin];
    uint8_t pin_  = dpins[pin];

    switch (port_) {
        case PORTB_:
            return (dval_t)(PINB & pin_);
        case PORTD_:
            return (dval_t)(PIND & pin_);
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