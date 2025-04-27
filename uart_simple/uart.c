#include "uart.h"
#include <util/delay.h>

int main(void) {
    uint16_t val = 0xDEAD;
    USART_init();

    while (1) {
        USART_send_string("Hello, AVR!\r\n");
        USART_send_scalar(val);
        _delay_ms(1000);
    }

    return 0;
}

