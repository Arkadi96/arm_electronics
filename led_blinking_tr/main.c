#include <avr/io.h>
#include <util/delay.h>

#define led PB5
#define port_sec DDRB

#define led_on port_sec |= (1 << led)
#define led_sc port_sec |= (0 << led)

int main() {
	led_on;
	while (1) {
		_delay_ms(1000);
		led_sc;
	}
    return 0;
}

