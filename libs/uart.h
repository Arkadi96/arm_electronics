#ifndef USART_H
#define USART_H

#include <avr/io.h>

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

uint8_t USART_receive() {
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

// Non blocked version of USAR_receive
uint8_t USART_receive_nb() {
    if (UCSR0A & (1 << RXC0))
		return UDR0;
	else
		return 0;
}

void USART_send(char data) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = data;
}

void USART_send_scalar(uint16_t v) {
    char buffer[6];
    uint8_t i = 0;

    if (v == 0) {
        USART_send('0');
    } else {
        while (v > 0) {
            buffer[i++] = '0' + (v % 10);
            v /= 10;
        }
        while (i--) {
            USART_send(buffer[i]);
        }
    }
    USART_send('\n');
}

void USART_send_string(const char *str) {
    while (*str) {
        USART_send(*str);
        str++;
    }
}

#endif
