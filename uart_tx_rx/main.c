#include "uart.h"
#include <util/delay.h>

#define LED_PIN PB0

void init_led() {
	DDRB |= (1 << LED_PIN); // set PB0 as output
}

int main(void) {
	init_led();
    USART_init();
	uint8_t st = 0;
	char c;
    while (1) {
		c = USART_receive_nb();
		switch (c) {
			case 'n':
				st |= 1 << 0;
				break;
			case 's':
				st |= 1 << 1;
				break;
			case 'l':
				st |= 1 << 2;
				break;
			case 'x':
				st |= 1 << 3;
				break;
			case 't':
				st |= 1 << 4;
				break;
			default:
				st |= st;
		}

		if ((st & 0x03) == 1) {
			st &= ~(1 << 0);
			USART_send_string("Name\r\n");
		}
		if ((st & 0x03) == 2) {
			st &= ~(1 << 1);
			USART_send_string("Surname\r\n");
		}
		if ((st & 0x04) == 4) {
			st &= ~(1 << 2);
			st &= ~(1 << 4);
			DDRB |= (1 << LED_PIN);
		}
		else if ((st & 0x08) == 8) {
			st &= ~(1 << 3);
			st &= ~(1 << 4);
			DDRB &= ~(1 << LED_PIN);
		}
		else if ((st & 0x10) == 16) {
			static uint16_t cnt = 0;
			if (cnt >= 10000) {
				DDRB ^= (1 << LED_PIN);
				cnt = 0;
			}
			cnt++;
		}
	}
    return 0;
}

