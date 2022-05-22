#pragma once

#include <arduino.h>

class IBatteryDriver
{
public:
    virtual uint8_t readBatteryLevel() = 0;
};