#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"

#ifndef DEBUG
#define DEBUG
#endif

#define LED_PIN PB1 // PWM

static uint16_t s_reading;

void init_led() {
	DDRB |= (1 << LED_PIN);
}

void init_adc() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN)  |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    DIDR0 |= (1 << ADC0D);
    ADCSRA |= (1 << ADSC);
}

void init_pwm() {
	// Enable fast pwm, clear time or compare
	TCCR1A |= (1 << WGM10);
	TCCR1B |= (1 << WGM12);
	// Clear OC1A/OC1B
	TCCR1A |= (1 << COM1A1);
	// Set prescaler to 64 (250 kHz clock)
	TCCR1B |= (1 << CS11) | (1 << CS10);
	// Set compare match A interrupt
	TIMSK1 |= (1 << OCIE1A);
	// Clear flag, this flag is being automatically
	// cleared when we use TIMER_COMPA_vect ISR function
	TIFR1 |= (1 << OCF1A);
	// Enable global interrupt SREG I bit -> 1
	OCR1A = 256;
}

uint16_t get_raw() {
    uint8_t low = ADCL;
    uint8_t high = ADCH;
    return (high << 8) | low;
}

void rotary_sensor_reading() {
	while (ADCSRA & (1 << ADSC));
	s_reading = get_raw();
	ADCSRA |= (1 << ADSC);
	USART_send_scalar(s_reading);
}

void adjust_pwm() {
	uint8_t s_r = s_reading / 4; // 0.25 is scale factor
	// Constrain the counter not to reach maximum values
	// 5% is good
	if (s_r <= 12) s_r = 12;
	if (s_r >= 243) s_r = 243;

	OCR1A = s_r;
}

ISR(TIMER1_COMPA_vect){
	rotary_sensor_reading();
	adjust_pwm();
	USART_send_string("I");
}

int main(void) {
	init_led();
    init_adc();
	init_pwm();
	sei();
#ifdef DEBUG
    USART_init();
#endif
    while (1) { }

    return 0;
}

