#include <avr/io.h>
#include "uart.h"

#define LED_PIN1 PB5
#define LED_PIN2 PD1

static int cnt = 0;

void led_init(void) {
	DDRB |= (1 << LED_PIN1);
	DDRD |= (1 << LED_PIN2);
}

void timer1_init(void) {
	TCCR1B |= (1 << CS12) | (1 << CS10);
	TCNT1 = 62410;        // 1 sec.
	TIFR1 |= (1 << TOV1); // Clear overflow flag
}

void setup(void) {
	led_init();
	timer1_init();
}

void delay_0p2s(void) {
	while (!(TIFR1 & (1 << TOV1)));
	TCNT1 = 62410;
	TIFR1 |= (1 << TOV1);
}

void switch_led1() {
	if (cnt % 5 == 0) {
		PORTB |= (1 << LED_PIN2);
	}
}

void switch_led2() {
	if (cnt % 10 == 0) {
		PORTD |= (1 << LED_PIN2);
	}
}

int main(void) {
	setup();
	while (1) {
		switch_led1(); // changes state every 1 sec
		switch_led2(); // changes state every 2 sec
		delay_0p2s();
		PORTB &= ~(1 << LED_PIN1);
		PORTD &= ~(1 << LED_PIN2);
		cnt += 1; 	// each cnt is 0.2 sec
	}
	return 0;
}

