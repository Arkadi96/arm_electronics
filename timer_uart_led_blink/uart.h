#include <avr/io.h>
#include <util/delay.h>

#ifndef F_CPU
#define F_CPU 16000000UL
#endif    
#define BAUD_RATE 9600
#define MY_UBRR F_CPU/16/BAUD_RATE-1

void USART_init(void) {
    unsigned int ubrr = MY_UBRR;
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

void USART_send(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_send_string(const char *str) {
    while (*str) {
        USART_send(*str);
        str++;
    }
}

