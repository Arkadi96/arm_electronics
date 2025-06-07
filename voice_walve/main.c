#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
//#include "uart.h"

#define VOICE_PIN PD5

#define N_DIV 16000000 / ( 2 * 1024 ) // freq / (prescaler * 2)

#define NL  0           // Null

// Octave 3
#define C3  N_DIV / 131 // 1  Do
#define CD3	N_DIV / 139 // 2  Do#
#define D3	N_DIV / 147 // 3  Re
#define DE3	N_DIV / 156 // 4  Re#
#define E3	N_DIV / 165 // 5  Mi
#define F3	N_DIV / 175 // 6  Fa
#define FG3	N_DIV / 185 // 7  Fa#
#define G3	N_DIV / 196 // 8  Sol
#define GA3	N_DIV / 208 // 9  Sol#
#define A3	N_DIV / 220 // 10 La
#define AB3	N_DIV / 233 // 11 La#
#define B3	N_DIV / 247 // 12 Si
// Octave 4
#define C4  N_DIV / 262 // 1  Do
#define CD4	N_DIV / 277 // 2  Do#
#define D4	N_DIV / 294 // 3  Re
#define DE4	N_DIV / 311 // 4  Re#
#define E4	N_DIV / 323 // 5  Mi
#define F4	N_DIV / 350 // 6  Fa
#define FG4	N_DIV / 370 // 7  Fa#
#define G4	N_DIV / 392 // 8  Sol
#define GA4	N_DIV / 416 // 9  Sol#
#define A4	N_DIV / 440 // 10 La
#define AB4	N_DIV / 466 // 11 La#
#define B4	N_DIV / 494 // 12 Si

// ~1 second (62 * 16ms)
#define S0P0 0  // 0.0  s
#define S0P1 6  // 0.1  s
#define S0P2 11 // 0.2  s
#define S0P3 21 // 0.33 s
#define S0P5 36 // 0.5  s
#define S0P7 52 // 0.7  s
#define S1P0 62 // 1.0  s
#define S1P2 78 // 1.2  s
#define S1P5 98 // 1.5  s

volatile uint16_t tick_count = 0;
volatile uint8_t current_note = 0;

volatile uint8_t delay[] = {
		S1P5, S1P2, S1P2,
		S1P2, S1P2, S1P0,
		S1P0, S1P0, S0P7,
		S0P7, S0P7, S0P5,
		S0P5, S0P5, S0P3,
		S0P3, S0P3, S0P3,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2, //
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2, //
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2,
		S0P2, S0P2, S0P2
	};

volatile uint8_t note[] = {
		C4,  E4,  A4,
		C4,  E4,  A4,
		C4,  E4,  A4,
		C4,  E4,  A4,
		C4,  E4,  A4,
		A3,  E4,  A4,
		C4,  E4,  A4,
		B3,  E4,  A4,
		C4,  E4,  A4,
		C4,  E4,  A4,
		C4,  E4,  A4,
		E3,  E4,  A4,
		B3,  E4,  A4,
		B3,  E4,  A4,
		B3,  E4,  G4,
		B3,  E4,  G4,
		B3,  E4,  G4,
		E3,  E4,  G4,
		B3,  E4,  G4
	};

void init_voice_pin()
{
	DDRD |= (1 << VOICE_PIN);
	PORTD &= ~(1 << VOICE_PIN);
}

void init_voice_timer()
{
	// Enabling CTC mode.
	TCCR1B |= (1 << WGM12);
	// Enable CTC interrupt
	TIMSK1 |= (1 << OCIE1A);
	// Enable 1024 prescaler
	TCCR1B |= (1 << CS12) | (1 << CS10);
}

void init_delay_timer()
{
	// Enabling CTC mode.
    TCCR0A = (1 << WGM01);
	// Enable 1024 prescaler
    TCCR0B = (1 << CS02) | (1 << CS00);
    OCR0A = 249; // 16ms interval
	// Enable Timer0 compare match interrupt
    TIMSK0 = (1 << OCIE0A);
}

ISR(TIMER1_COMPA_vect, ISR_BLOCK)
{
	if (current_note) {
		PORTD ^= (1 << VOICE_PIN);
		OCR1A = current_note;
	} else {
		PORTD |= (0 << VOICE_PIN);
	}
}

ISR(TIMER0_COMPA_vect, ISR_BLOCK) {
    tick_count++;
}

int main(void) {
	//USART_init();
	sei();
	init_voice_pin();
	init_voice_timer();
	init_delay_timer();

	uint8_t i = 0;
	current_note = note[i];
	while (1) {
		if (tick_count >= delay[i]) {
			tick_count = 0;
			if ((sizeof(delay) / sizeof(delay[0])) - 1 == i)
				i = 0;
			else
				i++;
			current_note = note[i];
		}
	}
	return 0;
}

