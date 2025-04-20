#ifndef SEGMENT_H
#define SEGMENT_H

/*
    2
   ---
1 |   | 3
  | 0 |
   ---
4 |   | 6
  | 5 |
   ---
        *7
*/

#include <stdint.h>
#include <avr/io.h>

#define LED_PIN_0 PB0
#define LED_PIN_1 PB1
#define LED_PIN_2 PD2
#define LED_PIN_3 PD3
#define LED_PIN_4 PD4
#define LED_PIN_5 PD5
#define LED_PIN_6 PD6
#define LED_PIN_7 PD7

#define DIGIT_ENA_PIN_0 PB2
#define DIGIT_ENA_PIN_1 PB3
#define DIGIT_ENA_PIN_2 PB4
#define DIGIT_ENA_PIN_3 PB5

#define DIGIT_0 0b01111110
#define DIGIT_1 0b01001000
#define DIGIT_2 0b00111101
#define DIGIT_3 0b01101101
#define DIGIT_4 0b01001011
#define DIGIT_5 0b01100111
#define DIGIT_6 0b11110111
#define DIGIT_7 0b01001100
#define DIGIT_8 0b01111111
#define DIGIT_9 0b11101111

#define LETTER_A 0b01011111
#define LETTER_B DIGIT_8
#define LETTER_C 0b10110110
#define LETTER_D DIGIT_0
#define LETTER_E 0b00110111
#define LETTER_F 0b10010111
#define LETTER_G 0b10010111
#define LETTER_H 0b01011011
#define LETTER_I DIGIT_1
#define LETTER_J 0b01101000
#define LETTER_K 0b01101000
#define LETTER_L 0b00110010
#define LETTER_S DIGIT_5
#define LETTER_O DIGIT_0

#define _GET_LED(x) LED_PIN_##x
#define GET_LED(x) _GET_LED(x)
#define _GET_DIGIT_ENA(x) DIGIT_ENA_PIN_##x
#define GET_DIGIT_ENA(x) _GET_DIGIT_ENA(x)
#define _GET_DIGIT(x) DIGIT_##x
#define GET_DIGIT(x) _GET_DIGIT(x)
#define _GET_LETTER(x) LETTER_##x
#define GET_LETTER(x) _GET_LETTER(x)

#define SET_PORT_BIT(port_idx, bit)                    \
    do {                                               \
        if (port_idx > 1 && port_idx < 8)              \
            PORTD |= (1 << (bit));                     \
        else                                           \
            PORTB |= (1 << (bit));                     \
    } while(0)

#define UNSET_PORT_BIT(port_idx, bit)                  \
    do {                                               \
        if (port_idx > 1 && port_idx < 8)              \
            PORTD &= ~(1 << (bit));                    \
        else                                           \
            PORTB &= ~(1 << (bit));                    \
    } while(0)

#define SET_DDR_BIT(port_idx, bit)                     \
    do {                                               \
        if (port_idx > 1 && port_idx < 8)              \
            DDRD |= (1 << (bit));                      \
        else                                           \
            DDRB |= (1 << (bit));                      \
    } while(0)

void digit_ena_on(uint8_t idx) {
    switch (idx) {
        case 0:
            UNSET_PORT_BIT(8, GET_DIGIT_ENA(0));
            break;
        case 1:
            UNSET_PORT_BIT(9, GET_DIGIT_ENA(1));
            break;
        case 2:
            UNSET_PORT_BIT(10, GET_DIGIT_ENA(2));
            break;
        case 3:
            UNSET_PORT_BIT(11, GET_DIGIT_ENA(3));
            break;
        default:
            UNSET_PORT_BIT(8, GET_DIGIT_ENA(0));
    }
}

void digit_ena_off(uint8_t idx) {
    switch (idx) {
        case 0:
            SET_PORT_BIT(8, GET_DIGIT_ENA(0));
            break;
        case 1:
            SET_PORT_BIT(9, GET_DIGIT_ENA(1));
            break;
        case 2:
            SET_PORT_BIT(10, GET_DIGIT_ENA(2));
            break;
        case 3:
            SET_PORT_BIT(11, GET_DIGIT_ENA(3));
            break;
        default:
            SET_PORT_BIT(8, GET_DIGIT_ENA(0));
    }
}

static void led_on(uint8_t idx) {
    switch (idx) {
        case 0:
            SET_PORT_BIT(0, GET_LED(0));
            break;
        case 1:
            SET_PORT_BIT(1, GET_LED(1));
            break;
        case 2:
            SET_PORT_BIT(2, GET_LED(2));
            break;
        case 3:
            SET_PORT_BIT(3, GET_LED(3));
            break;
        case 4:
            SET_PORT_BIT(4, GET_LED(4));
            break;
        case 5:
            SET_PORT_BIT(5, GET_LED(5));
            break;
        case 6:
            SET_PORT_BIT(6, GET_LED(6));
            break;
        case 7:
            SET_PORT_BIT(7, GET_LED(7));
            break;
        default:
            SET_PORT_BIT(7, GET_LED(7));
    }
}

static void led_off(uint8_t idx) {
    switch (idx) {
        case 0:
            UNSET_PORT_BIT(0, GET_LED(0));
            break;
        case 1:
            UNSET_PORT_BIT(1, GET_LED(1));
            break;
        case 2:
            UNSET_PORT_BIT(2, GET_LED(2));
            break;
        case 3:
            UNSET_PORT_BIT(3, GET_LED(3));
            break;
        case 4:
            UNSET_PORT_BIT(4, GET_LED(4));
            break;
        case 5:
            UNSET_PORT_BIT(5, GET_LED(5));
            break;
        case 6:
            UNSET_PORT_BIT(6, GET_LED(6));
            break;
        case 7:
            UNSET_PORT_BIT(7, GET_LED(7));
            break;
        default:
            UNSET_PORT_BIT(7, GET_LED(7));
    }
}

// Init LEDs for sensor
// cnt - LEDs count in 7 segment sensor
void init_segment(uint8_t cnt) {
    SET_DDR_BIT(0, GET_LED(2));
    SET_DDR_BIT(1, GET_LED(3));
    SET_DDR_BIT(2, GET_LED(4));
    SET_DDR_BIT(3, GET_LED(5));
    SET_DDR_BIT(4, GET_LED(6));
    SET_DDR_BIT(5, GET_LED(7));
    SET_DDR_BIT(6, GET_LED(0));
    SET_DDR_BIT(7, GET_LED(1));

    switch (cnt) {
        case 2:
            SET_DDR_BIT(8, GET_DIGIT_ENA(0));
            SET_DDR_BIT(9, GET_DIGIT_ENA(1));
            break;
        case 3:
            SET_DDR_BIT(8, GET_DIGIT_ENA(0));
            SET_DDR_BIT(9, GET_DIGIT_ENA(1));
            SET_DDR_BIT(10, GET_DIGIT_ENA(2));
            break;
        case 4:
            SET_DDR_BIT(8, GET_DIGIT_ENA(0));
            SET_DDR_BIT(9, GET_DIGIT_ENA(1));
            SET_DDR_BIT(10, GET_DIGIT_ENA(2));
            SET_DDR_BIT(11, GET_DIGIT_ENA(3));
            break;
        default:
            SET_DDR_BIT(8, GET_DIGIT_ENA(0));
    }
}

// Tunrs all leds off
void turn_seg_off() {
    uint8_t i = 0;
    for (; i < 8; i++) {
        led_off(i);
    }
    i = 0;
    for (; i < 4; i++) {
        digit_ena_off(i);
    }
}

// Tunrs all leds on
void turn_seg_on() {
    uint8_t i = 0;
    for (; i < 8; i++) {
        led_on(i);
    }
    i = 0;
    for (; i < 4; i++) {
        digit_ena_on(i);
    }
}

// Tunrs digit on
// c - letter
// idx - led number
uint8_t display_digit(uint8_t c, uint8_t idx) {
    if (c > 9) {
        return 0;
    }
    turn_seg_off();
    uint8_t i = 0;
    uint8_t s_led;
    switch (c) {
        case 0:
            s_led = GET_DIGIT(0);
            break;
        case 1:
            s_led = GET_DIGIT(1);
            break;
        case 2:
            s_led = GET_DIGIT(2);
            break;
        case 3:
            s_led = GET_DIGIT(3);
            break;
        case 4:
            s_led = GET_DIGIT(4);
            break;
        case 5:
            s_led = GET_DIGIT(5);
            break;
        case 6:
            s_led = GET_DIGIT(6);
            break;
        case 7:
            s_led = GET_DIGIT(7);
            break;
        case 8:
            s_led = GET_DIGIT(8);
            break;
        case 9:
            s_led = GET_DIGIT(9);
            break;
        default:
            s_led = GET_DIGIT(7);
    }
    for (; i < 8; i++) {
        if (s_led & (1 << i)) {
            led_on(i);
        }
    }
    digit_ena_on(idx);
    return 1;
}

// Display letter on sensor
// c - letter
// idx - led number
uint8_t display_char(char c, uint8_t idx) {
    turn_seg_off();
    uint8_t i = 0;
    uint8_t s_led;
    switch (c) {
        case 'H':
            s_led = GET_LETTER(H);
            break;
        case 'E':
            s_led = GET_LETTER(E);
            break;
        case 'L':
            s_led = GET_LETTER(L);
            break;
        case 'O':
            s_led = GET_LETTER(O);
            break;
        default:
            s_led = GET_LETTER(E);
    }
    for (; i < 8; i++) {
        if (s_led & (1 << i)) {
            led_on(i);
        }
    }
    digit_ena_on(idx);
    return 1;
}

#endif
