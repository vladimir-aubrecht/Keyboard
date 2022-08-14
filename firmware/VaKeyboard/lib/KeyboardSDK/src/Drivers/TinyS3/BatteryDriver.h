#pragma once

#ifdef TINYS3

#include <arduino.h>
#include "../IBatteryDriver.h"

class BatteryDriver : public IBatteryDriver
{
public:
    BatteryDriver();

    virtual uint8_t readBatteryLevel();
};

#endif