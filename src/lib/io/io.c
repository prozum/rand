#include <io.h>

void set_pin_mode(dpin_t pin, pin_mode_t pm)
{
    // lookup the port value in dports
    uint8_t port_ = dports[pin];

    // lookup the pin value
    uint8_t pin_  = dpins[pin];

    switch (port_) {
        case PORTB_:
            // if the port is PORTB_ then set the pin in DDRB to the pinmode
            DDRB |= (pin_ * pm);
            break;
        case PORTD_:
            // if the port is PORTD_ then set the pin in DDRD to the pinmode
            DDRD |= (pin_ * pm);
            break;
        default:
            LOG_ERROR(SENDER_IO, "Trying to set pin mode of invalid pin.");
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
        case PORTB_:
            // if the port is PORTB_ then write ps to the pin in PORTB
            PORTB |= (pin_ * ps);
            break;
        case PORTD_:
            // if the port is PORTD_ then write ps to the pin in PORTD
            PORTD |= (pin_ * ps);
            break;
        default:
            LOG_ERROR(SENDER_IO, "Trying to write to invalid pin.");
    }
}

dval_t digital_read(dpin_t pin)
{
    uint8_t port_ = dports[pin];
    uint8_t pin_  = dpins[pin];

    switch (port_) {
        case PORTB_:
            // if the port is PORTB_ then return the pin's value in PORTB
            return (dval_t)(PINB & pin_);
        case PORTD_:
            // if the port is PORTD_ then return the pin's value in PORTD
            return (dval_t)(PIND & pin_);
        default:
            LOG_ERROR(SENDER_IO, "Trying to read from invalid pin.");
    }
}

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout)
{
    uint8_t pin_ = dpins[pin];
    uint8_t port_ = dports[pin];
    uint8_t state_ = (state ? pin_ : 0);
    uint16_t width = 0;

    uint16_t loop_count = 0;
    uint16_t loop_max = MS_TO_CLOCK_CYCLES(timeout) / 16; // maybe bitshift with 4 instead

    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    while (((volatile uint8_t)port_to_input[port_]) & pin_ != state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }

        width++;
    }

    return CLOCK_CYCLES_TO_MS(width * 21 + 16);
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