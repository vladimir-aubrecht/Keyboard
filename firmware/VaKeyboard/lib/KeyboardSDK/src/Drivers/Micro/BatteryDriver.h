#pragma once

#ifdef ARDUINO_MICRO

#include <arduino.h>
#include "../IBatteryDriver.h"

class BatteryDriver : public IBatteryDriver
{
public:
    BatteryDriver();

    virtual uint8_t readBatteryLevel();
};

#endif