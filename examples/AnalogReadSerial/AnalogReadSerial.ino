/*
  AnalogReadSerial - I2C master
  Reads an analog input on pin 0 of slave, prints the result to the serial monitor 
  The slave is connected with master using I2C bus.
*/

#include "Wire.h"      // You need to include both Wire.h and mArduino.h
#include "mArduino.h"

const int SLAVE_ADDRESS = 1;

void setup()  { 
  Wire.begin();         // join I2C bus as a Master  
  Serial.begin(9600);
} 

void loop()
{
  int sensorValue = analogRead(SLAVE_ADDRESS, A0);
  Serial.println(sensorValue);  
  delay(100);
}

