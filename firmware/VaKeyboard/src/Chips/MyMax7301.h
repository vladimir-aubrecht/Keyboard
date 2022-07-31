#pragma once
#include <Arduino.h>
#include <SPI.h>

class MyMax7301
{
private:
    uint8_t csPin;
    SPISettings spiSettings;

public: 
    MyMax7301(uint8_t csPin);
    void begin();
    uint8_t readGPIORegister(uint8_t address);
    void writeGPIORegister(uint8_t address, uint8_t value);
};