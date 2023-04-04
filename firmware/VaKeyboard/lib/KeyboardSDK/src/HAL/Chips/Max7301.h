#pragma once
#include <Arduino.h>

class Max7301
{
private:
    uint8_t csPin = 11;
    uint8_t mosiPin = 10;
    uint8_t sclkPin = 9;
    uint8_t misoPin = 13;
    byte transferByte(byte data_out);
    uint8_t transferWord(uint8_t higherByte, uint8_t lowerByte);

public: 
    Max7301(uint8_t csPin, uint8_t mosiPin, uint8_t sclkPin, uint8_t misoPin);
    void begin();
    uint8_t read(uint8_t address);
    void write(uint8_t address, uint8_t value);
    void enable();
};