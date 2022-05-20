#pragma once

#include <arduino.h>

class BatteryDriver
{
public:
    BatteryDriver();

    uint8_t readBatteryLevel();
};