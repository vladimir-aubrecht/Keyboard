#pragma once
#include "Arduino.h"

class IRGBLedDriver
{
    public:
        virtual void turnOn() = 0;
        virtual void turnOff() = 0;
        virtual bool toggle() = 0;
        virtual void blink(uint8_t animationPhase, uint8_t x, uint8_t y, uint32_t color) = 0;
        virtual void randomizeColors() = 0;
        virtual void setColor(uint8_t x, uint8_t y, uint8_t redIntensity, uint8_t greenIntensity, uint8_t blueIntensity) = 0;
};