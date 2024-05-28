#include "labvee.h"

#define KEYPAD_ADDRESS 0x20
#define TERMINAL_ADDRESS 0x21
#define DISPLAY_ADDRESS 0x22

uint16_t display_value = 0;
uint16_t terminal_value = 0;

uint8_t portDIGITAL(uint8_t terminal, uint8_t pin)
{
  uint16_t actual_value = portI2C_read16(TERMINAL_ADDRESS);
  uint8_t phisical_pin = ((terminal - 1) * 4) + pin;
  return (actual_value & (1 << phisical_pin));
}

void portDIGITAL(uint8_t terminal, uint8_t pin, uint8_t state)
{
  bitWrite(terminal_value, (((terminal - 1) * 4) + pin), state);
  portI2C_write16(TERMINAL_ADDRESS, terminal_value);
}

uint8_t keypadWaitValue()
{
  uint8_t keypadvalue = 0;
  while (!keypadvalue)
  {
    keypadvalue = keypadGetValue();
  }
  return keypadvalue;
}

uint8_t keypadGetValue()
{
  for (uint8_t pinO = 0; pinO < 4; pinO++)
  {
    portI2C_write16(KEYPAD_ADDRESS, (1 << pinO));
    uint16_t value = portI2C_read16(KEYPAD_ADDRESS);
    if (value & (1 << 4))
      return (pinO * 4) + 1;
    if (value & (1 << 5))
      return (pinO * 4) + 2;
    if (value & (1 << 6))
      return (pinO * 4) + 3;
    if (value & (1 << 7))
      return (pinO * 4) + 4;
  }
  return 0;
}

void displayReset(uint8_t display)
{
  uint8_t aux = (display == 2) ? 8 : 0;
  display_value &= (0x00FF << aux);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displayReset()
{
  portI2C_write16(DISPLAY_ADDRESS, 0);
}

void displayWrite(uint8_t display, uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10)
  {
    uint8_t aux = (display == 2) ? 8 : 0;
    display_value = dv[value] | ((0x00FF << aux) & display_value);
    portI2C_write16(DISPLAY_ADDRESS, display_value);
  }
}

void displayWrite(uint8_t value)
{
  const uint8_t dv[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 100)
  {
    uint8_t dec = value / 10;
    uint8_t unit = value % 10;
    display_value = dv[unit] | (dv[dec] << 8);
    portI2C_write16(DISPLAY_ADDRESS, display_value);
  }
}

void displayDP(uint8_t display, uint8_t value)
{
  uint8_t aux = (display == 2) ? D2_DP : D1_DP;
  bitWrite(display_value, aux, value);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displaySegment(uint8_t display, uint8_t segment, uint8_t value)
{
  uint8_t aux = (display == 2) ? 8 : 0;
  bitWrite(display_value, aux + segment, value);
  portI2C_write16(DISPLAY_ADDRESS, display_value);
}

void displaySegment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP)
{
}