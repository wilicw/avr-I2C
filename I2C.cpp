#ifndef F_CPU
#define F_CPU 8000000UL
#endif
#include "I2C.h"
#include "MSB.h"
#include <util/delay.h>

I2C::I2C(volatile uint8_t *PORT_W, volatile uint8_t *PORT_R, volatile uint8_t *PORT_MODE, uint8_t __SDA, uint8_t __SCL, uint8_t __device_address)
    : port_write(PORT_W), port_read(PORT_R), port_mode(PORT_MODE), SCL(__SCL), SDA(__SDA), device_address(__device_address) {
        SCL_mask = _BV(__SCL);
        SDA_mask = _BV(__SDA);
        *port_write &= ~SCL_mask;
        *port_mode &= ~SCL_mask;
        *port_write &= ~SDA_mask;
        *port_mode &= ~SDA_mask;
}

void I2C::begin() {
    /* start condition */
    // Set SDA to LOW
    *port_mode |= SDA_mask;
    // Set SCL to LOW
    *port_mode |= SCL_mask;
}

void I2C::end() {
    /* stop condition */
    // Set ACK to HIGH
    *port_mode &= ~SCL_mask;
    // Set SDA to HIGH
    *port_mode &= ~SDA_mask;
}

bool I2C::isACK() {
    bool state = true;
    *port_mode &= ~SDA_mask;
    // Set SCL to HIGH
    *port_mode &= ~SCL_mask;
    // ACK means SDA pull to LOW
    if (*port_read & SDA_mask) {
        state = false;
    }
    // Set SCL to LOW
    *port_mode |= SCL_mask;
    return state;
}

bool I2C::send(const uint8_t __data) {
    uint8_t len = 8;
    uint8_t MSB_data = MSB_lookup_table[__data];
    while (len --> 0) {
        // Set SCL to LOW
        *port_mode |= SCL_mask;
        if (MSB_data % 2) {
            *port_mode &= ~SDA_mask;
        } else {
            *port_mode |= SDA_mask;
        }
        MSB_data /= 2;
        // Set SCL to HIGH
        *port_mode &= ~SCL_mask;
    }
    *port_mode |= SCL_mask;
    *port_mode |= SDA_mask;
    return isACK();
}

void I2C::set_address(const uint8_t RW) {
    const uint8_t sending_data = (device_address << 1) + RW;
    send(sending_data);
    return;
}
