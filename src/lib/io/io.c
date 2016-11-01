#include "../io_priv.h"
#include <stdlib.h>
#include <string.h>

#if !MOCK

void set_pin_mode(dpin_t pin, pin_mode_t pm)
{
    if (pm != OUTPUT && pm != INPUT) {
        LOG_ERROR_BYPASS("Invalid pin mode used in set_pin_mode");
        return;
    } else if (pin > MAXIMUM_PIN) {
        LOG_ERROR_BYPASS("Non-existing pin in set_pin_mode");
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
            DDRB = (DDRB & ~pin_) | (pin_ * pm);
            break;
        case PORTD_:
            DDRD = (DDRD & ~pin_) | (pin_ * pm);
            break;
        default:
            LOG_ERROR(SENDER_IO, "Trying to set invalid pin in set_pin_mode");
    }
}

void digital_write(dpin_t pin, dval_t ps)
{
    if (ps != HIGH && ps != LOW) {
        LOG_ERROR_BYPASS("Invalid digital value used in digital_write");
        return;
    } else if (pin > MAXIMUM_PIN) {
        LOG_ERROR_BYPASS("Non-existing pin in digital_write");
        return;
    }

    // lookup the port value based on a pin
    uint8_t port_ = dports[pin];

    // lookup the pin value based on a pin
    uint8_t pin_  = dpins[pin];

    switch (port_) {
        case PORTB_:
            PORTB = (PORTB & ~pin_) | (pin_ * ps);
            break;
        case PORTD_:
            PORTD |= (PORTD & ~pin_) | (pin_ * ps);
            break;
        default:
            LOG_ERROR(SENDER_IO, "Trying to write to invalid pin in set_pin_mode");
    }
}

dval_t digital_read(dpin_t pin)
{
    if (pin > MAXIMUM_PIN) {
        LOG_ERROR_BYPASS("Non-existing pin in digital_read");
        return LOW;
    }

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
            LOG_ERROR(SENDER_IO, "Trying to read from invalid pin in digital_read");
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


void uart_putchar(char c/*, FILE *stream*/) {
    loop_until_bit_is_set(UCSR0A, UDRE0); // wait while register is free
    UDR0 = c;
}

char uart_getchar(/*FILE *stream*/) {
    loop_until_bit_is_set(UCSR0A, RXC0); /* Wait until data exists. */
    return UDR0;
}

void serial_write_string(tx_t pin, char *out){
    int i;
    for(i = 0; i < strlen(out)-1;i++) {
        uart_putchar(out[i]);
    }

}

char* serial_read_string(tx_t pin, int len ) {
    char* str = malloc(sizeof(char)*(len+1));

    int i;
    for(i=0;i<len;i++){
        str[i] = uart_getchar();
    }
    str[i+1] = '\0';
    return str;
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

#else

#define DIGITAL_PINS 13
#define DIGITAL_BUFFER_SIZE 5
#define SERIAL_PINS 1
#define SERIAL_BUFFER_SIZE 5

void set_pin_mode(dpin_t pin, pin_mode_t pm) { }

dval_t digital_read_val;

dval_t digital_read(dpin_t pin)
{
    return digital_read_val;
}

char uart_val;

char uart_getchar() {
    return uart_val;
}

uint16_t pulse_in(dpin_t pin, dval_t state, uint16_t timeout) { }

//13 is the number of digital pins on the board and 5 is the buffer size
dval_t digital_buffer[DIGITAL_PINS][DIGITAL_BUFFER_SIZE];
uint8_t dig_buf_cnt [DIGITAL_PINS];
void digital_write(dpin_t pin, dval_t ps) {
    //Increments the counter and makes sure it does not exceed buffer size
    dig_buf_cnt[pin] = (dig_buf_cnt[pin] + 1) % DIGITAL_BUFFER_SIZE;
    //Set the value of the digital write buffer to the value specified.
    digital_buffer[pin][dig_buf_cnt[pin]] = ps;
}

dval_t get_digital_buffer(dpin_t pin, uint8_t index) {
    if (pin < DIGITAL_PINS && pin >= 0) {
        if(index < DIGITAL_BUFFER_SIZE && index > DIGITAL_BUFFER_SIZE) {
             return digital_buffer[pin][index];
        }
    }

    return -1;
}

void uart_init() { }

void uart_putchar(char c) { }

char **write_buffer;
void serial_write_string(tx_t pin, char *out) {
    if(write_buffer) {
        free(write_buffer);
    }
    write_buffer = malloc(strlen(out) * sizeof(char));
    strcpy(write_buffer, out);
}
char *get_write_buffer() {
    return write_buffer;
}
void clear_write_buffer() {
    if(write_buffer) {
        free(write_buffer);
    }
}

char *serial_string_val;

char* serial_read_string(tx_t pin, int len ) {
    return serial_string_val;
}

#endif