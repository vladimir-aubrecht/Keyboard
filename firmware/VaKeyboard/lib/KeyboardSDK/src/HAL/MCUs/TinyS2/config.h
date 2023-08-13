#pragma once

#ifdef TINYS2

#include "Arduino.h"

class McuConfig
{
    public:
        static const uint8_t csPin = 14;
        static const uint8_t mosiPin = 38;
        static const uint8_t sclkPin = 36;
        static const uint8_t misoPin = 37;
};

#endif