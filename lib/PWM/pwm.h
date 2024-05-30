#include "Arduino.h"
#include "Wire.h"

uint8_t portPWM(uint8_t pin,uint16_t toff,uint8_t ton);
uint16_t portPWM(uint8_t pin);
uint8_t portPWM_setFrecuency(float frecuency);