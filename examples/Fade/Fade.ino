/*
  Fade - I2C master
  This example shows how to fade slave's LED on pin 9
  The slave is connected with master using I2C bus.
*/

#include "Wire.h"      // You need to include both Wire.h and mArduino.h
#include "mArduino.h"

const int SLAVE_ADDRESS = 1;
const int ledPin = 9;
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by

void setup()  { 
  Wire.begin();         // join I2C bus as a Master  
  pinMode(ledPin, OUTPUT);
} 

void loop()  { 
  // set the brightness of ledPin
  analogWrite(SLAVE_ADDRESS, ledPin, brightness);    

  // change the brightness for next time through the loop:
  brightness = brightness + fadeAmount;

  // reverse the direction of the fading at the ends of the fade: 
  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     
  // wait for 30 milliseconds to see the dimming effect    
  delay(30);                            
}
