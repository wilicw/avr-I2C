#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include "I2C.h"
#include <util/delay.h>

I2C::I2C(volatile uint8_t *PORT_W, volatile uint8_t *PORT_R, volatile uint8_t *PORT_MODE, uint8_t __SDA, uint8_t __SCL, uint8_t __device_address)
    : port_write(PORT_W), port_read(PORT_R), port_mode(PORT_MODE), SCL(__SCL), SDA(__SDA), device_address(__device_address) {
        SCL_mask = 1 << __SCL;
        SDA_mask = 1 << __SDA;
        *port_mode |= SCL_mask;
        *port_mode |= SDA_mask;
        *port_write |= SCL_mask;
        *port_write |= SDA_mask;
}

void I2C::begin() {
    /* start condition */
    *port_write &= 0xff ^ SDA_mask;
    _delay_us(5);
    *port_write &= 0xff ^ SCL_mask;
    _delay_us(5);
}

bool I2C::isACK() {
    bool state = true;
    *port_write |= SCL_mask;
    *port_mode &= 0xff ^ SDA_mask; // change SDA to read mode (0)
    _delay_us(3);
    if (*port_read & SDA_mask) {
        state = false;
    }
    _delay_us(3);
    *port_write &= 0xff ^ SCL_mask;
    *port_mode |= SDA_mask; // change SDA to write mode (1)
    return state;
}

void I2C::end() {
    /* stop condition */
    *port_write |= SCL_mask;
    _delay_us(5);
    *port_write |= SDA_mask;
    _delay_us(5);
}

void I2C::send(const uint8_t __data) {
    uint8_t len = 7;
    while (len --> 0) {
        
    }
}
