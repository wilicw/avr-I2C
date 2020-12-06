#define F_CPU 8000000L
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"

constexpr uint8_t LED = 7;
constexpr uint8_t LED_mask = 1 << LED;

void init() {
    DDRC |= LED_mask;
    PORTC &= 0xff ^ LED_mask;
    return;
}

int main() {
    I2C device(&PORTD, &PIND, &DDRD, 0, 1, 0x3c);
    init();
    while (true) {
        PORTC ^= LED_mask;
        _delay_ms(100);
    }
    return 0;
}
