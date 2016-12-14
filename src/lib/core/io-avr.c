#include "core/io.h"
#include "core/log.h"

#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/eeprom.h>

#define NOT_A_PORT 0
const uint16_t port_to_input[] = {
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) & PINB,
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) & PINC,
        NOT_A_PORT,
        NOT_A_PORT,
        (uint16_t) & PIND,
};

void set_pin_mode(dpin_t pin, pin_mode_t pm) {
    if (pm != OUTPUT && pm != INPUT) {
        ERROR("Invalid pin mode used in set_pin_mode");
        return;
    } else if (pin > MAXIMUM_PIN) {
        ERROR("Non-existing pin in set_pin_mode");
        return;
    }

    // lookup the port value in dports
    uint8_t port_ = dports[pin];

    // lookup the pin value
    uint8_t pin_ = dpins[pin];

    switch (port_) {
        case PORTB_:
            // (DDRx & ~pin_) cancels out the pin mode, so it's 0
            // | pin_ then sets the pin mode to 0 or 1 according to it's value
            DDRB = ((DDRB & ~pin_) | (pin_ * pm));
            break;
        case PORTD_:
            DDRD = ((DDRD & ~pin_) | (pin_ * pm));
            break;
        default:
            WARNING(SENDER_IO, "Trying to set invalid pin in set_pin_mode");
    }
}

void digital_write(dpin_t pin, dval_t ps) {
    if (ps != HIGH && ps != LOW) {
        WARNING(SENDER_IO, "Invalid digital value used in digital_write");
        return;
    } else if (pin > MAXIMUM_PIN) {
        ERROR("Non-existing pin in digital_write");
        return;
    }

    // lookup the port value based on a pin
    uint8_t port_ = dports[pin];

    // lookup the pin value based on a pin
    uint8_t pin_ = dpins[pin];

    switch (port_) {
        case PORTB_:
            PORTB = (PORTB & ~pin_) | (pin_ * ps);
            break;
        case PORTD_:
            PORTD |= (PORTD & ~pin_) | (pin_ * ps);
            break;
        default:
            ERROR("Trying to write to invalid pin in set_pin_mode");
    }
}

dval_t digital_read(dpin_t pin) {
    if (pin > MAXIMUM_PIN) {
        ERROR("Non-existing pin in digital_read");
        return LOW;
    }

    uint8_t port_ = dports[pin];
    uint8_t pin_ = dpins[pin];

    switch (port_) {
        case PORTB_:
            // if the port is PORTB_ then return the pin's value in PORTB
            return (dval_t)(PINB & pin_);
        case PORTD_:
            // if the port is PORTD_ then return the pin's value in PORTD
            return (dval_t)(PIND & pin_);
        default:
            ERROR("Trying to read from invalid pin in digital_read");
    }
}

void uart_init() {
    UBRR0H = UBRRH_VALUE;
    UBRR0L = UBRRL_VALUE;
#if USE_2X
    UCSR0A |= _BV(U2X0);
#else
    UCSR0A &= ~(_BV(U2X0));
#endif
    UCSR0C = _BV(UCSZ01) | _BV(UCSZ00); /* 8-bit data */
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);   /* Enable RX and TX */
}


void uart_putchar(char c) {
    while (!(UCSR0A & (1 << UDRE0))); // wait while register is free
    UDR0 = c;
}

char uart_getchar() {
    while (!(UCSR0A) & (1 << RXC0)); /* Wait until data exists. */
    return UDR0;
}

char uart_trygetchar() {
    if (!(UCSR0A & (1 << UDRE0))) {  /* if unread data exists. */
        return UDR0;
    }
    return '\0'; //return \0 if no unread data is found.
}

void serial_write_string(tx_t pin, char *out) {
    uint8_t i;
    uint8_t len = strlen(out);

    if(len > MAX_IO_STR_LEN)
        return;

    for (i = 0; i < strlen(out); i++) { //(out[i] != '\0')
        uart_putchar(out[i]);
    }

}

char *serial_read_string(tx_t pin, uint8_t len) {
    char *str = malloc(sizeof(char) * (len + 1));

    uint8_t i;
    for (i = 0; i < len; i++) {
        str[i] = uart_getchar();
    }
    str[i + 1] = '\0';
    return str;
}

char *serial_read_string_nowait(tx_t pin, uint8_t len) {
    char *str = malloc(sizeof(char) * (len + 1));
    str[0] = uart_trygetchar();
    if (str[0] != '\0') {
        uint8_t i;
        for (i = 0; i < len; i++) {
            str[i] = uart_getchar();
        }
        str[i + 1] = '\0';
        return str;
    }
    return NULL;
}

void adc_init() {
    ADCSRA |= ((1 << ADPS2) | (1 << ADPS1) |
               (1 << ADPS0)); // set prescaler bits in ADCSRA(ADC control and status register A)

    ADMUX |= (1 << REFS0);
    ADMUX &= ~(1 << REFS1); //Set mode: (Set reference voltage to 5V input)

    ADCSRB &= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0)); //set free running mode in control and status register B
    ADMUX = (ADMUX & 0xF0) | (0x00); //set default reading pin(Analog 0)

    ADCSRA |= (1<<ADATE);               //Enable auto trigger
    ADCSRA |= (1<<ADEN);                //Enable ADC power supply
    ADCSRA |= (1<<ADSC);                //Start first conversion(will run automatically from then on.)
}

void analog_read_setpin(apin_t pin) {
    ADMUX = (ADMUX & 0xF0) | (pin & 0x0F);  //select ADC channel safely
}

uint16_t analog_read() {
    return ADC;
}

void eeprom_write(uint16_t p, uint8_t value)
{
#if DEBUG
    char buffer[64];
    sprintf(buffer,"write| addr: %d value: %d\n", (uint8_t *)p, value);
    serial_write_string(SERIAL0, buffer);
#endif
    eeprom_write_byte((uint8_t *)p, value);
}

uint8_t eeprom_read(uint16_t p)
{
    uint8_t value = eeprom_read_byte((uint8_t *)p);
#if DEBUG
    char buffer[64];
    sprintf(buffer,"read| addr: %d value: %d\n", (uint8_t *)p, value);
    serial_write_string(SERIAL0, buffer);
#endif
    return value;
}

void eeprom_show()
{
    char tmp[16];
    int i = 0;

    for (i; i < EEPROM_SIZE; ++i) {
        sprintf(tmp, "%d", eeprom_read(i));
        serial_write_string(USB_TX, tmp);
    }
}

/**
 * Reads a pulse on the specified pin
 * @param pin to read from
 * @param state the pulse starts with this value
 * @param timeout the maximum time in microseconds to wait for the pulse
 * @return 1 if the value was read, 0 otherwise
 */
/*
uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout)
{
    uint8_t pin_ = dpins[pin];
    uint8_t port_ = dports[pin];
    uint8_t state_ = (state ? pin_ : 0);

    uint16_t loop_count = 0;
    uint16_t loop_max = MS_TO_CLOCK_CYCLES(timeout) / 16; //16 clock-cycles pr. loop-iteration?

    //Read first instance of the pulse
    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    //Read the following opposite pulse value, i.e. the duck (HIGH-LOW-HIGH) or raise (LOW-HIGH-LOW)
    while (((volatile uint8_t)port_to_input[port_]) & pin_ != state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    //Read the last part of the pulse
    while (((volatile uint8_t)port_to_input[port_]) & pin_ == state_)
    {
        if (loop_count++ == loop_max)
        {
            return 0;
        }
    }

    return 1;
}
 */