#pragma once

#ifdef FEATHER_ESP32_S3_NOPSRAM

#include "Arduino.h"

class McuConfig
{
    public:
        static const uint8_t csPin = 9;
        static const uint8_t mosiPin = 6;
        static const uint8_t sclkPin = 5;
        static const uint8_t misoPin = 10;
};

#endif