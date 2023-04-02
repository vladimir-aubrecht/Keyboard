#pragma once

#ifdef ARDUINO_MICRO

#include "Arduino.h"

class McuConfig
{
     public:
        static const uint8_t csPin = 11;
        static const uint8_t mosiPin = 10;
        static const uint8_t sclkPin = 9;
        static const uint8_t misoPin = 13;
};

#endif