#include "i2c.h"

void portI2C_begin()
{
    Wire.begin();
}

uint8_t portI2C_read8(const uint8_t address)
{
    uint8_t data_in = 0;
    if (Wire.requestFrom(address, (uint8_t)1) != 1)
    {
        return data_in;
    }
    data_in = Wire.read();
    return data_in;
}

uint8_t portI2C_write8(const uint8_t address, const uint8_t value)
{
    Wire.beginTransmission(address);
    Wire.write(value);
    return Wire.endTransmission();
}

uint16_t portI2C_read16(const uint8_t address)
{
    uint16_t data_in = 0;
    if (Wire.requestFrom(address, (uint8_t)2) != 2)
    {
        return data_in;
    }
    data_in = Wire.read();
    data_in |= (Wire.read() << 8);
    return data_in;
}

uint8_t portI2C_write16(const uint8_t address, const uint16_t value)
{
    Wire.beginTransmission(address);
    Wire.write(value & 0xFF);
    Wire.write(value >> 8);
    return Wire.endTransmission();
}

uint8_t portI2C_readBytes(const uint8_t address, uint8_t *buffer, size_t len)
{
    size_t recv = Wire.requestFrom(address, len);
    if (recv != len)
        return false;
    for (size_t i = 0; i < len; i++)
    {
        buffer[i] = Wire.read();
    }
    return true;
}

uint8_t portI2C_writeBytes(const uint8_t address, uint8_t *value, size_t len)
{
    Wire.beginTransmission(address);
    Wire.write(value, len);
    return Wire.endTransmission();
}

uint8_t portI2C_writeBytes(const uint8_t address, uint8_t *value, size_t len,
                           uint8_t *prefix_value, size_t prefix_len)
{
    Wire.beginTransmission(address);
    Wire.write(value, len);
    Wire.write(prefix_value, prefix_len);
    return Wire.endTransmission();
}