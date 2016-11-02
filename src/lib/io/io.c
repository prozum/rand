#if MOCK
#include "io-mock.c"
#else
#include "io-avr.c"
#endif


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

void analog_write(apin_t pin, aval_t out)
{

}

aval_t analog_read(apin_t pin)
{

}