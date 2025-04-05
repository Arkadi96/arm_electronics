#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN PD7
#define LED_PIN PD6

static uint8_t is_led_on = 0;

void init() 
{
	DDRD &= ~(1 << BUTTON_PIN);
	PORTD |= (1 << BUTTON_PIN);
	DDRD |= (1 << LED_PIN);
}

uint8_t is_button_pressed()
{
	return !(PIND & (1 << BUTTON_PIN));
}

void change_led_state(uint8_t v)
{
	if (v)
		PORTD ^= (1 << LED_PIN);	
	else
		PORTD &= ~(1 << LED_PIN);	
}

int main(void)
{
	init();
	while (1) {
		if (is_button_pressed()) {
			if (is_led_on)
				change_led_state(0);
			else
				change_led_state(1);
			is_led_on = ~is_led_on;
		}
		_delay_ms(500);
	}

	return 0;
}

