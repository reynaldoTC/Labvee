#include "Arduino.h"
#include "Wire.h"

void portI2C_begin();
uint8_t portI2C_read8(const uint8_t address);
uint8_t portI2C_write8(const uint8_t address, const uint8_t value);
uint16_t portI2C_read16(const uint8_t address);
uint8_t portI2C_write16(const uint8_t address, const uint16_t value);
uint8_t portI2C_readBytes(const uint8_t address, uint8_t *buffer, size_t len);
uint8_t portI2C_writeBytes(const uint8_t address, const uint8_t *value, size_t len);
uint8_t portI2C_writeBytes(const uint8_t address, const uint8_t *value, size_t len, uint8_t *prefix_value, size_t prefix_len);