#include <Arduino.h>
#include "labvee.h"

void setup() {
  // put your setup code here, to run once:
/*
  portDIGITAL(termina,pin,state)
  portDIGITAL(termina,pin)
  portGPIO(pin,state)
  portGPIO(pin)
  portADC(pin)
  portPWM(pin,frecuencia,ton)
  portSPI(dato)
  portUART.begin(115200);
  portUART.println("holamundo")
  portI2C(dir,dato)
*/
  portUART_begin();
  portI2C_begin();
}

void loop() {
  // put your main code here, to run repeatedly:

  displayWrite(keypadWaitValue());
  delay(1000);
  displayReset();
  for (uint8_t i = 0; i < 10; i++) {
    displayWrite(i);
    delay(500);
  }
}
