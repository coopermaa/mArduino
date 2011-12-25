// General_slave.ino
// Refer to master examples for use with this
#include <Wire.h>          // You need to include both Wire.h and mArduino.h
#include "mArduino.h"

const int SLAVE_ADDRESS = 1;

void setup()
{
  mArduino(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
}

void loop()
{
}
