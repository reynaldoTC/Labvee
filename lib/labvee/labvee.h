#pragma once

#include "i2c.h"
#include <Arduino.h>

#define D1_A 0
#define D1_B 1
#define D1_C 2
#define D1_D 3
#define D1_E 4
#define D1_F 5
#define D1_G 6
#define D1_DP 7

#define D2_A 8
#define D2_B 9
#define D2_C 10
#define D2_D 11
#define D2_E 12
#define D2_F 13
#define D2_G 14
#define D2_DP 15

#define DISPLAY_U 1
#define DISPLAY_D 2

#define portUART Serial
#define portUART_begin() Serial.begin(115200)

uint8_t portDIGITAL(uint8_t terminal, uint8_t pin);
void portDIGITAL(uint8_t terminal, uint8_t pin, uint8_t state);

uint8_t keypadWaitValue();
uint8_t keypadGetValue();

void displayReset(uint8_t display);
void displayReset();
void displayWrite(uint8_t display, uint8_t value);
void displayWrite(uint8_t value);
void displayDP(uint8_t display, uint8_t value);
void displaySegment(uint8_t display, uint8_t segment, uint8_t value);
void displaySegment(uint8_t display, uint8_t A, uint8_t B, uint8_t C, uint8_t D, uint8_t E, uint8_t F, uint8_t G, uint8_t DP);

