#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include "segment.h"

void display_0_to_9() {
    uint8_t i;
    i = 0;
    for (; i < 10; i++) {
        display_digit(i);
        _delay_ms(500);
    }
}

int main(void)
{
    init_segment();
    while (1) {
        display_0_to_9();
    }
    return 0;
}

