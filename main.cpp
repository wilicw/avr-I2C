#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include <avr/io.h>
#include <util/delay.h>
#include "I2C.h"

constexpr uint8_t LED = 7;
constexpr uint8_t LED_mask = 1 << LED;

void init() {
    DDRC |= LED_mask;
    PORTC &= ~LED_mask;
    return;
}

int main() {
    I2C device(&PORTD, &PIND, &DDRD, 0, 1, 0x3c);
    bool state = false;
    init();
    while (true) {
        device.begin();
        state = device.send(0b11001101);
        if (state) {
            PORTC ^= LED_mask;
            _delay_us(10);
            PORTC ^= LED_mask;
        }
        device.end();
        _delay_us(100);

    }
    return 0;
}
