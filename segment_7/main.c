#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "segment.h"

void display_0_to_9() {
    uint8_t i;
    i = 0;
    for (; i < ; i++) {
        display_digit(i, 0);
        _delay_ms(500);
    }
}

void display_HELLO() {
    display_char('H', 0);
    _delay_ms(500);
    display_char('E', 0);
    _delay_ms(500);
    display_char('L', 0);
    _delay_ms(500);
    display_char('L', 0);
    _delay_ms(500);
    display_char('O', 0);
    _delay_ms(500);
}

int main(void)
{
    init_segment(4);
    while (1) {
        //display_0_to_9();
        display_HELLO();
    }
    return 0;
}

