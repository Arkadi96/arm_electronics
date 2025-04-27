#include <avr/io.h>
#include <util/delay.h>

#define LED_0 PB0
#define LED_1 PB1
#define LED_2 PB2

void init_adc() {
    ADMUX = (1 << REFS0);
    ADCSRA = (1 << ADEN)  |
             (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    DIDR0 |= (1 << ADC0D);
}

void init_leds() {
    DDRB |= (1 << LED_0);
    DDRB |= (1 << LED_1);
    DDRB |= (1 << LED_2);
}

uint16_t get_raw() {
    uint8_t low = ADCL;
    uint8_t high = ADCH;
    return (high << 8) | low;
}

void rotary_sensor_reading(uint16_t *r) {
    ADCSRA |= (1 << ADSC);
    while (ADCSRA & (1 << ADSC));
    *r = get_raw();
}

void led_display(uint16_t r) {
    PORTB &= ~((1 << PB0) | (1 << PB1) | (1 << PB2));
    if (r <= 341) {
        PORTB |= (1 << PB0);
    }
    else if (r <= 682) {
        PORTB |= (1 << PB1);
    }
    else {
        PORTB |= (1 << PB2);
    }
}

int main() {
    init_adc();
    init_leds();

    uint16_t reading;
    while (1) {
        rotary_sensor_reading(&reading);
        led_display(reading);
        _delay_ms(100);
    }

    return 0;
}

