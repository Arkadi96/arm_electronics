#include "uart.h" 
#include <util/delay.h>

int main(void) {
    USART_init();

    while (1) {
        USART_send_string("Hello, AVR!\r\n");
        _delay_ms(1000);
    }

    return 0;
}

