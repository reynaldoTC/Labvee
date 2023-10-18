#pragma once

#include "PCF8575.h"
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

#define ONE 1
#define TWO 2
#define THREE 3
#define FOUR 4

#define UNO 1
#define DOS 2
#define TRES 3
#define CUATRO 4

extern PCF8575 keypad(0x20);
extern PCF8575 labveeIO(0x21);
extern PCF8575 display_7seg(0x22);

#define terminalRead(TERMINAL, PIN) (labveeIO.digitalRead(((TERMINAL-1)*4)+PIN))
#define terminalWrite(TERMINAL, PIN, STATE) (labveeIO.digitalWrite((((TERMINAL-1)*4)+PIN), STATE))
#define terminalMode(TERMINAL, PIN, MODE) (labveeIO.pinMode((((TERMINAL-1)*4)+PIN), MODE))

#define terminalOneRead(PIN) (labveeIO.digitalRead(PIN - 1))
#define terminalOneWrite(PIN, STATE) (labveeIO.digitalWrite(PIN, STATE))
#define terminalOneMode(PIN, MODE) (labveeIO.pinMode(PIN, MODE))

#define terminalTwoRead(PIN) (labveeIO.digitalRead(3 + PIN))
#define terminalTwoWrite(PIN, STATE) (labveeIO.digitalWrite((3 + PIN), STATE))
#define terminalTwoMode(PIN, MODE) (labveeIO.pinMode((3 + PIN), MODE))

#define terminalThreeRead(PIN) (labveeIO.digitalRead(7 + PIN))
#define terminalThreeWrite(PIN, STATE) (labveeIO.digitalWrite((7 + PIN), STATE))
#define terminalThreeMode(PIN, MODE) (labveeIO.pinMode((7 + PIN), MODE))

#define terminalFourRead(PIN) (labveeIO.digitalRead(11 + PIN))
#define terminalFourWrite(PIN, STATE) (labveeIO.digitalWrite((11 + PIN), STATE))
#define terminalFourMode(PIN, MODE) (labveeIO.pinMode((11 + PIN), MODE))

#define teminalInit() labveeIO.begin()


/* ---------------------------- 16 BUTTONS KEYPAD --------------------------- */
/* ------- FUNCTIONS TO CONTROL, INIT AND GET VALUES FRONM THE KEYPAD ------- */
void keypadInit(){
  keypad.pinMode(P0, OUTPUT);
  keypad.pinMode(P1, OUTPUT);
  keypad.pinMode(P2, OUTPUT);
  keypad.pinMode(P3, OUTPUT);
  keypad.pinMode(P4, INPUT);
  keypad.pinMode(P5, INPUT);
  keypad.pinMode(P6, INPUT);
  keypad.pinMode(P7, INPUT);

  keypad.begin();
}

uint8_t keypadWaitValue(){
  byte keypadvalue = 0;
  while(!keypadvalue){
    keypadvalue = keypadgetValue();
  }
}

uint8_t keypadgetValue(){
  for (byte pinO = 0; pinO < 4; pinO++){
    keypad.digitalWrite(pinO, HIGH);
    for (byte pinI = 4; pinI < 8; pinI){
      if (keypad.digitalRead(pinI)){
        return (pinI*4) + pinI + 1;
      }
    }
    keypad.digitalWrite(pinO, LOW);
  }
  return 0;
}
/* ----------------------------------------------------------------------------- */

/* --------------------------- 7 SEGMENTS DISPLAY --------------------------- */
/* ----- FUNCTIONS TO INITIALIZE, DISPLAY NUMERIC VALUES AND SET SEGMENTS ------ */
void displayInit(uint8_t display){
  if (display == 1){
    display_7seg.pinMode(D1_A, OUTPUT);
    display_7seg.pinMode(D1_B, OUTPUT);
    display_7seg.pinMode(D1_C, OUTPUT);
    display_7seg.pinMode(D1_D, OUTPUT);
    display_7seg.pinMode(D1_E, OUTPUT);
    display_7seg.pinMode(D1_F, OUTPUT);
    display_7seg.pinMode(D1_G, OUTPUT);
    display_7seg.pinMode(D1_DP, OUTPUT);
  }else if(display == 2){
    display_7seg.pinMode(D2_A, OUTPUT);
    display_7seg.pinMode(D2_B, OUTPUT);
    display_7seg.pinMode(D2_C, OUTPUT);
    display_7seg.pinMode(D2_D, OUTPUT);
    display_7seg.pinMode(D2_E, OUTPUT);
    display_7seg.pinMode(D2_F, OUTPUT);
    display_7seg.pinMode(D2_G, OUTPUT);
    display_7seg.pinMode(D2_DP, OUTPUT);
  }
  display_7seg.begin();
}

void displayWrite(uint8_t display, uint8_t value){
  const byte displayvalues[10] = {63, 6, 91, 79, 102, 109, 125, 7, 127, 111};
  if (value < 10){
    byte aux = 0;
    if (display == 1){
      aux = 0;
    }else if(display == 2){
      aux = 8;
    }
    for (byte i = 0; i < 8; i++){
      display_7seg.digitalWrite(i + aux, bitRead(displayvalues[value], i));
    }
  }
}

void displayDP(uint8_t display, uint8_t value){
  if (display == 1){
    display_7seg.digitalWrite(D1_DP, value);
  }else if (display == 2){
    display_7seg.digitalWrite(D2_DP, value);
  }
}

void displayPIN(uint8_t display, uint8_t pin, uint8_t value){
  if (display == 1){
    const byte pins[8] = {D1_A, D1_B, D1_C, D1_D, D1_E, D1_F, D1_G, D1_DP};
    display_7seg.digitalWrite(pins[pin], value);
  }else if (display == 2){
    const byte pins[8] = {D2_A, D2_B, D2_C, D2_D, D2_E, D2_F, D2_G, D2_DP};
    display_7seg.digitalWrite(pins[pin], value);
  }
}
/* ----------------------------------------------------------------------------- */
