#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
//#include "uart.h"

#define BUTTON_PIN PD7
#define LED_PIN PD6

void init() 
{
	DDRD &= ~(1 << BUTTON_PIN);
	PORTD |= (1 << BUTTON_PIN);
	DDRD |= (1 << LED_PIN);
}

int main(void) {
	init();
	while (1) {
		if (!(PIND & (1 << BUTTON_PIN))) {
			PORTD ^= (1 << LED_PIN);	
			_delay_ms(500);
		} else {
			PORTD &= ~(1 << LED_PIN);	
		}
	}

	return 0;
}

