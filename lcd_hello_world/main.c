#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "lcd1602.h"
//#include "uart.h"

int main(void) {
	//USART_init();
	LCD1605_init();
	while (1) {
		LCD1605_write();
		_delay_ms(1000);
	}
	return 0;
}

