/*
 * DigitalAdvanced.cpp - DigitalAdvanced library for Arduino
 * Copyright (c) 2011 Cooper Maa.  All right reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include "mArduino.h"

byte requestRegister;
uint8_t pin = 0;

void mArduino()
{
  Wire.begin();         // join I2C bus as a Master 
}

void mArduino(uint8_t address)
{
  Wire.begin(address);    // join I2C bus as a slave with specified address
  Wire.onReceive(receiveEvent); // register event
  Wire.onRequest(requestEvent); // register event    
}

void pinMode(int slave_addr, uint8_t pin, uint8_t mode)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(PIN_MODE);
  Wire.write(pin);
  Wire.write(mode);
  Wire.endTransmission();        
}

// make a digitalRead request from slave
int digitalRead(int slave_addr, uint8_t pin)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(DIGITAL_READ);
  Wire.write(pin);
  Wire.endTransmission();  
  
  delay(1);   // allot the slave some processing time
  
  Wire.requestFrom(slave_addr, 1);
  return Wire.read();  
}

// make a digitalWrite request from slave
void digitalWrite(int slave_addr, uint8_t pin, uint8_t value)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(DIGITAL_WRITE);
  Wire.write(pin);
  Wire.write(value);
  Wire.endTransmission();      
}

// make a analogRead request from slave
int analogRead(int slave_addr, uint8_t pin)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(ANALOG_READ);
  Wire.write(pin);
  Wire.endTransmission();    
  
  delay(1);   // allot the slave some processing time

  // analog data is a 2-byte value
  Wire.requestFrom(slave_addr, 2);  
  byte lowByte  = Wire.read();     // read low byte first
  byte highByte =  Wire.read();    // then high byte
  int value = (highByte << 8) | lowByte;   
  return value;
}

// make a analogWrite request from slave
void analogWrite(int slave_addr, uint8_t pin, int value)
{
  Wire.beginTransmission(slave_addr);
  Wire.write(ANALOG_WRITE);
  Wire.write(pin);
  
  // analog data is a 2-byte value
  byte packet[2];
  packet[0] = (byte) value;
  packet[1] = (byte) (value >> 8);
  Wire.write(packet, 2);  
  Wire.endTransmission();        
}

// function that executes whenever data is received from master
void receiveEvent(int howMany)
{
  int value, mode;
  
  requestRegister = Wire.read();
  pin = Wire.read(); 
  
  switch (requestRegister)  
  {
    case PIN_MODE:
      mode = Wire.read();
      pinMode(pin, mode);
      break;
    case DIGITAL_WRITE:
      value = Wire.read();
      digitalWrite(pin, value);
      break;
    case ANALOG_WRITE:
      // analog data is a 2-byte value
      byte lowByte  = Wire.read();     // read low byte first
      byte highByte =  Wire.read();    // then high byte
      value = (highByte << 8) | lowByte;
      analogWrite(pin, value);
      break;
  }
}

// function that executes whenever data is requested by master
void requestEvent()
{
  int pinStatus;
  int value;
  
  switch (requestRegister)
  {
    case DIGITAL_READ:
      pinStatus = digitalRead(pin);
      Wire.write(pinStatus);  
    case ANALOG_READ:
      value = analogRead(pin);

      // analog data is a 2-byte value
      byte packet[2];
      packet[0] = (byte) value;
      packet[1] = (byte) (value >> 8);
      Wire.write(packet, 2);
      break;
  }
}
