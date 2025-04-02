#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "uart.h"

#define LED_PIN PB5

volatile uint8_t tick_signal = 0;

void init() 
{
	DDRB |= (1 << LED_PIN);
	PORTB &= ~(1 << LED_PIN);

	// Enabling CTC mode.
	TCCR1B |= (1 << WGM12);
	// Compare value (1s)
	OCR1A = 15625;
	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A);
	// Enable 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
	// Enable global interrupt SREG I bit -> 1
	sei();
}

// Interrupt handler, ISR_BLOCK - initially global interrupts disabled
ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
        //USART_send_string("tck! \n");
	tick_signal++;
}

int main(void) {
    	//USART_init();
	init();
	while (1)
		if (tick_signal) {
			PORTB ^= (1 << LED_PIN);
			tick_signal = 0;
		}
	return 0;
}

