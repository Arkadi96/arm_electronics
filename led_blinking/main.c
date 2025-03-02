#include <avr/io.h>
#include <util/delay.h>

int main() {
    DDRB |= (1 << PB5);  // Set PB5 (Digital Pin 13 on Arduino) as output

    while (1) {
        PORTB ^= (1 << PB5); // Toggle LED
        _delay_ms(10000);
    }

    return 0;
}

