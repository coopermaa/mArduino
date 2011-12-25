/*
 * DigitalAdvanced.h - DigitalAdvanced library for Arduino
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

#ifndef mArduino_h
#define mArduino_h
#include "Arduino.h"
#include "Wire.h"


const byte PIN_MODE      = 0x00;
const byte DIGITAL_READ  = 0x10;
const byte DIGITAL_WRITE = 0x11;
const byte ANALOG_READ   = 0x20;
const byte ANALOG_WRITE  = 0x21;

void mArduino(); 
void mArduino(uint8_t);

// API for Master
void pinMode(int slave_addr, uint8_t pin, uint8_t mode);
int digitalRead(int slave_addr, uint8_t pin);
void digitalWrite(int slave_addr, uint8_t pin, uint8_t value);
int analogRead(int slave_addr, uint8_t pin);
void analogWrite(int slave_addr, uint8_t pin, int value);

// callbacks for Slave
void receiveEvent(int howMany);
void requestEvent();

#endif