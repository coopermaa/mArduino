/*
  Blink - I2C master
  Turns on slave's LED on for one second, then off for one second, repeatedly.
  The slave is connected with master using I2C bus.
*/

#include "Wire.h"      // You need to include both Wire.h and mArduino.h
#include "mArduino.h"

const int SLAVE_ADDRESS = 1;
const int ledPin = 13;

void setup()
{
  mArduino();            // join I2C bus as a Master    
  pinMode(SLAVE_ADDRESS, ledPin, OUTPUT);  
}  

void loop() {
  digitalWrite(SLAVE_ADDRESS, ledPin, HIGH);
  delay(100);
  digitalWrite(SLAVE_ADDRESS, ledPin, LOW);
  delay(100);
}
