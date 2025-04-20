#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "segment.h"

static uint8_t L_COUNT = 5;
static uint8_t TCK = 5; // Ticks of display "freez"

void display_HELLO(uint8_t c) {
    uint8_t tck = TCK;
    do {
        switch (c) {
            case 0:
                display_char('H', 3);
                _delay_ms(80);
                break;
            case 1:
                display_char('H', 2);
                _delay_ms(40);
                display_char('E', 3);
                _delay_ms(40);
                break;
            case 2:
                display_char('H', 1);
                _delay_ms(27);
                display_char('E', 2);
                _delay_ms(27);
                display_char('L', 3);
                _delay_ms(27);
                break;
            case 3:
                display_char('H', 0);
                _delay_ms(20);
                display_char('E', 1);
                _delay_ms(20);
                display_char('L', 2);
                _delay_ms(20);
                display_char('L', 3);
                _delay_ms(20);
                break;
            case 4:
                display_char('E', 0);
                _delay_ms(20);
                display_char('L', 1);
                _delay_ms(20);
                display_char('L', 2);
                _delay_ms(20);
                display_char('O', 3);
                _delay_ms(20);
                break;
            case 5:
                display_char('L', 0);
                _delay_ms(27);
                display_char('L', 1);
                _delay_ms(27);
                display_char('O', 2);
                _delay_ms(27);
                break;
            case 6:
                display_char('L', 0);
                _delay_ms(40);
                display_char('O', 1);
                _delay_ms(40);
                break;
            case 7:
                display_char('O', 0);
                _delay_ms(80);
                break;
            default:
                _delay_ms(20);
        }
    } while (tck--);
}

int main(void)
{
    uint8_t c = 0;
    init_segment(4);
    while (1) {
        if (c == L_COUNT * 2 - 1) c = 0;
        display_HELLO(c);
        c++;
    }
    return 0;
}

