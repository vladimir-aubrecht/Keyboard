#ifdef ARDUINO_MICRO

// I had issues to force platformIO to install it properly as dependency, therefore temporarely copying it.
// This file is copy from here:
// https://github.com/jfjlaros/max7301

/* MAXIM 7301 GPIO port expander. */
#include "max7301.h"


/**
 * Constructor.
 *
 * @arg {byte} pinCLK - Clock pin.
 * @arg {byte} pinDIN - Data In pin.
 * @arg {byte} pinDOUT - Data Out pin.
 * @arg {byte} pinCS - Chip select pin.
 * @arg {bool} x - Select model AAX.
 */
MAX7301::MAX7301(byte pinCLK, byte pinDIN, byte pinDOUT, byte pinCS, bool x) {
  _pinCLK = pinCLK;
  _pinDIN = pinDIN;
  _pinDOUT = pinDOUT;
  _pinCS = pinCS;
  
  ::pinMode(_pinCLK, OUTPUT);
  ::pinMode(_pinDIN, OUTPUT);
  ::pinMode(_pinDOUT, INPUT_PULLUP);
  ::pinMode(_pinCS, OUTPUT);

  ::digitalWrite(_pinCLK, LOW);
  ::digitalWrite(_pinCS, HIGH);

  if (!x) {
    // Not model AAX, disable unavailable pins.
    write(0x09, 0x55);
    write(0x0A, 0x55);
  }
}

/**
 * Write one byte to DIN, read one byte from DOUT.
 *
 * @arg {byte} data - Data.
 *
 * @return {byte} - Result.
 */
byte MAX7301::_transfer(byte data) {
  byte result = 0x00;
  int bit;

  for (bit = 7; bit >= 0; bit--) {
    ::digitalWrite(_pinCLK, LOW);
    ::digitalWrite(_pinDIN, (data & (0x01 << bit)));
    result |= ::digitalRead(_pinDOUT) << bit;
    ::digitalWrite(_pinCLK, HIGH);
  }
  ::digitalWrite(_pinCLK, LOW);

  return result;
}

/**
 * Read one byte from the specified addres.
 *
 * @arg {byte} address - Address.
 *
 * @return {byte} - Data.
 */
byte MAX7301::read(byte address) {
  byte result;

  ::digitalWrite(_pinCS, LOW);
  _transfer(address | 0x80);
  _transfer(NOP);
  ::digitalWrite(_pinCS, HIGH);

  ::digitalWrite(_pinCS, LOW);
  _transfer(NOP);
  result = _transfer(NOP);
  ::digitalWrite(_pinCS, HIGH);

  return result;
}

/**
 * Write one byte to the specified addres.
 *
 * @arg {byte} address - Address.
 * @arg {byte} data - Data.
 */
void MAX7301::write(byte address, byte data) { 
  ::digitalWrite(_pinCS, LOW);
  _transfer(address & ~0x80);
  _transfer(data);
  ::digitalWrite(_pinCS, HIGH);
}

/**
 * Set normal operation mode.
 */
void MAX7301::enable(void) {
  delay(2000);
  write(0x04, read(0x04) | 0x01);
}

/**
 * Set shutdown mode.
 */
void MAX7301::disable(void) {
  write(0x04, read(0x04) & ~0x01);
}

/**
 * Enable transition detection.
 */
void MAX7301::enableTransitionDetection(void) {
  write(0x04, read(0x04) | 0x80);
}

/**
 * Disable transition detection.
 */
void MAX7301::disableTransitionDetection(void) {
  write(0x04, read(0x04) & ~0x80);
}

/**
 * Configure transition detection mask.
 *
 * @arg {byte} pin - Pin number.
 * @arg {bool} mode - Mode.
 */
void MAX7301::configureTransitionDetection(byte pin, bool mode) {
  byte offset = pin - 24;

  write(0x06, read(0x06) & ~(0x01 << offset) | mode << offset);
}

/**
 * Get pin configuration.
 *
 * @arg {byte} pin - Pin number.
 *
 * @return {byte} - Pin configuration.
 */
byte MAX7301::getPinMode(byte pin) {
  return (read((pin / 4) + 0x08) >> (2 * (pin % 4))) & 0x03;
}

/**
 * Set pin configuration.
 *
 * @arg {byte} pin - Pin number.
 * @arg {byte} mode - Pin configuration.
 */
void MAX7301::pinMode(byte pin, byte mode) {
  byte reg = (pin / 4) + 0x08,
       offset = 2 * (pin % 4);

  write(reg, read(reg) & ~(0x03 << offset) | mode << offset);
}

/**
 * Read from a GPIO pin.
 *
 * @arg {byte} pin - Pin number.
 *
 * @return {byte} - Data.
 */
byte MAX7301::digitalRead(byte pin) {
  return read(pin + 0x20);
}

/**
 * Write to a GPIO pin.
 *
 * @arg {byte} pin - Pin number.
 * @arg {byte} data - Data.
 */
void MAX7301::digitalWrite(byte pin, byte data) {
  write(pin + 0x20, data);
}

/**
 * Read up to 8 consecutive GPIO pins.
 *
 * @arg {byte} pin - First pin number.
 *
 * @return {byte} - Data.
 */
byte MAX7301::digitalReadRange(byte pin) {
  return read(pin + 0x40);
}

/**
 * Write to up to 8 consecutive GPIO pins.
 *
 * @arg {byte} pin - First pin number.
 * @arg {byte} data - Data.
 */
void MAX7301::digitalWriteRange(byte pin, byte data) {
  write(pin + 0x40, data);
}

#endif