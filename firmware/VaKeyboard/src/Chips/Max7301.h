// I had issues to force platformIO to install it properly as dependency, therefore temporarely copying it.
// This file is copy from here:
// https://github.com/jfjlaros/max7301

#ifndef MAX7301_h
#define MAX7301_h

#include <Arduino.h>

#define NOP 0x00
#define GPIO_OUTPUT 0x01
#define GPIO_INPUT 0x02
#define GPIO_INPUT_PULLUP 0x03


class MAX7301 {
  public:
    MAX7301(byte, byte, byte, byte, bool);
    byte read(byte),
         getPinMode(byte),
         digitalRead(byte),
         digitalReadRange(byte);
    void write(byte, byte),
         enable(void),
         disable(void),
         enableTransitionDetection(void),
         disableTransitionDetection(void),
         configureTransitionDetection(byte, bool),
         pinMode(byte, byte),
         digitalWrite(byte, byte),
         digitalWriteRange(byte, byte);
  private:
    byte _transfer(byte),
         _pinCLK,
         _pinDIN,
         _pinDOUT,
         _pinCS;
};

#endif