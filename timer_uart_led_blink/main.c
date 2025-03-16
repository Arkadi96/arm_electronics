#include <avr/io.h>
#include "uart.h"

#define LED_PIN PB5

void led_init(void) {
	DDRB |= (1 << LED_PIN);
}

void timer1_init(void) {
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TCNT1 = 18661;
	TIFR1 |= (1 << TOV1); // Clear overflow flag
}

void setup(void) {
	led_init();
	USART_init();
	timer1_init();
}

void delay_3s(void) {
	while (!(TIFR1 & (1 << TOV1)));
}

int main(void) {
	setup();
	while (1) {
		delay_3s();
		TIFR1 |= (1 << TOV1);
		PORTB ^= (1 << LED_PIN);
	}
	return 0;
}

