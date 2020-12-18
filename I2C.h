#include <avr/io.h>
/*
 * I2C Class 
 * I2C (*port, *pin, *ddr, SDA pin, SCL pin, address)
 */
class I2C {
private:
    volatile uint8_t *port_write;
    volatile uint8_t *port_read;
    volatile uint8_t *port_mode;
    uint8_t SCL, SDA, SCL_mask, SDA_mask, device_address;
    void _to_default();

public:
    I2C(volatile uint8_t *, volatile uint8_t *, volatile uint8_t *, uint8_t, uint8_t, uint8_t);
    void begin();
    bool isACK();
    bool send(uint8_t);
    void end();
    void set_address(const uint8_t);
};
/* I2C Class */
