#pragma once

#include <arduino.h>
#include "Drivers/IBatteryDriver.h"

class BatteryDriver : public IBatteryDriver
{
public:
    BatteryDriver();

    virtual uint8_t readBatteryLevel();
};